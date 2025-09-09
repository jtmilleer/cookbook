import requests
from bs4 import BeautifulSoup
import json
import time
import os
import re

# Folder to save recipes
SAVE_DIR = r"C:\Users\jtmil\cookbook\recipes"
os.makedirs(SAVE_DIR, exist_ok=True)

# Base URL for topic page
TOPIC_URL = "https://cooking.nytimes.com/topics/easy-recipes"

HEADERS = {"User-Agent": "Mozilla/5.0"}

# Delay between requests (in seconds)
REQUEST_DELAY = 1.5

# Function to sanitize file names
def sanitize_filename(name):
    return re.sub(r'[^a-zA-Z0-9_\-]', '_', name)

# Function to clean text from control characters
def clean_text(text):
    return re.sub(r'[\x00-\x1F\x7F-\x9F]', '', text).strip()

# Function to get all recipe URLs from a topic page
def get_recipe_links(topic_url):
    recipe_links = set()
    page = 1
    while True:
        url = f"{topic_url}?page={page}"
        response = requests.get(url, headers=HEADERS)
        if response.status_code != 200:
            break
        soup = BeautifulSoup(response.text, "html.parser")
        # Each recipe link is inside <a data-testid="card-link" href="...">
        cards = soup.find_all("a", {"data-testid": "card-link"})
        if not cards:
            break  # No more recipes
        for card in cards:
            link = card.get("href")
            if link and link.startswith("/recipes/"):
                recipe_links.add("https://cooking.nytimes.com" + link)
        print(f"[INFO] Found {len(cards)} recipes on page {page}")
        page += 1
        time.sleep(REQUEST_DELAY)
    return list(recipe_links)

# Function to scrape a single recipe and save as JSON
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
        instructions = [clean_text(step.get("text", "")) for step in data.get("recipeInstructions", [])]

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

def main():
    print("[INFO] Collecting recipe links...")
    recipe_urls = get_recipe_links(TOPIC_URL)
    print(f"[INFO] Total recipes found: {len(recipe_urls)}")

    for i, url in enumerate(recipe_urls, 1):
        print(f"[INFO] Scraping recipe {i}/{len(recipe_urls)}: {url}")
        scrape_recipe(url)

if __name__ == "__main__":
    main()
