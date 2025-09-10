import requests
from bs4 import BeautifulSoup
import json
import time
import os
import re

# ----------------------------
# CONFIG
# ----------------------------
SAVE_DIR = r"C:\Users\jtmil\cookbook\recipes"
os.makedirs(SAVE_DIR, exist_ok=True)

COLLECTION_URL = "https://cooking.nytimes.com/68861692-nyt-cooking/126768340-most-popular-recipes-2025-so-far"

HEADERS = {"User-Agent": "Mozilla/5.0"}
REQUEST_DELAY = 1.5  # polite delay

# ----------------------------
# HELPERS
# ----------------------------
def sanitize_filename(name):
    return re.sub(r'[^a-zA-Z0-9_\-]', '_', name)

def clean_text(text):
    return re.sub(r'[\x00-\x1F\x7F-\x9F]', '', text).strip()

# ----------------------------
# GET RECIPE LINKS FROM COLLECTION PAGE
# ----------------------------
def get_recipe_links(collection_url):
    print(f"[INFO] Fetching collection page: {collection_url}")
    response = requests.get(collection_url, headers=HEADERS)
    response.raise_for_status()
    soup = BeautifulSoup(response.text, "html.parser")

    links = []
    scripts = soup.find_all("script", type="application/ld+json")
    for script in scripts:
        try:
            data = json.loads(script.string)
            if isinstance(data, dict) and "itemListElement" in data:
                for item in data["itemListElement"]:
                    url = item.get("url")
                    if url and url.startswith("https://cooking.nytimes.com/recipes/"):
                        links.append(url)
        except Exception:
            continue

    print(f"[INFO] Found {len(links)} recipes in collection")
    return links

# ----------------------------
# SCRAPE A SINGLE RECIPE
# ----------------------------
def scrape_recipe(recipe_url):
    try:
        response = requests.get(recipe_url, headers=HEADERS)
        if response.status_code != 200:
            print(f"[WARN] Failed to fetch {recipe_url}")
            return
        soup = BeautifulSoup(response.text, "html.parser")
        script_tag = soup.find("script", type="application/ld+json")
        if not script_tag:
            print(f"[WARN] No JSON-LD found for {recipe_url}")
            return
        data = json.loads(script_tag.string)
        if data.get("@type") != "Recipe":
            print(f"[WARN] Not a recipe: {recipe_url}")
            return

        title = clean_text(data.get("name", "Unnamed Recipe"))
        ingredients = [clean_text(i) for i in data.get("recipeIngredient", [])]
        instructions = []
        if "recipeInstructions" in data:
            for step in data["recipeInstructions"]:
                if isinstance(step, dict):
                    instructions.append(clean_text(step.get("text", "")))
                elif isinstance(step, str):
                    instructions.append(clean_text(step))

        recipe_json = {
            "title": title,
            "ingredients": ingredients,
            "instructions": instructions,
            "url": recipe_url
        }

        filename = os.path.join(SAVE_DIR, sanitize_filename(title) + ".json")
        with open(filename, "w", encoding="utf-8") as f:
            json.dump(recipe_json, f, ensure_ascii=False, indent=4)
        print(f"[INFO] Saved recipe: {title}")
        time.sleep(REQUEST_DELAY)
    except Exception as e:
        print(f"[ERROR] {recipe_url}: {e}")

# ----------------------------
# MAIN
# ----------------------------
def main():
    recipe_urls = get_recipe_links(COLLECTION_URL)
    print(f"[INFO] Total recipes to scrape: {len(recipe_urls)}")

    for i, url in enumerate(recipe_urls, 1):
        print(f"[INFO] Scraping recipe {i}/{len(recipe_urls)}: {url}")
        scrape_recipe(url)

if __name__ == "__main__":
    main()
