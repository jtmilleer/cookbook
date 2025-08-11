//
// Created by jtmil on 8/9/2025.
//

#include "Cookbook.h"
#include "Recipe.h"
#include "RecipeList.h"
#include <cassert>
#include <iostream>

void CookbookTest();

void RecipeListTest();

void RecipeListTestSize1();


Cookbook loadTestRecipies();

int main() {

    CookbookTest();

    return 0;
}

void CookbookTest() {
    Cookbook cookbook;

    const Recipe* potato = new Recipe("potato");
    const Recipe* meatball = new Recipe("meatball");
    const Recipe* muffin = new Recipe("muffin");
    const Recipe* junebug = new Recipe("junebug");


    cookbook.addRecipe(potato);

    cookbook.addRecipe(meatball);
    cookbook.addRecipe(muffin);
    cookbook.addRecipe(junebug);

    cookbook.print();

    /*
    assert(cookbook.getRecipeCount() == 4);
    cookbook.getLetter('M').print();

    std::cout << cookbook.getRecipe("junebug")->title << std::endl;
    cookbook.removeRecipe("d");
    cookbook.removeRecipe("junebug");
    */

}

void RecipeListTest() {
    RecipeList newList;

    const Recipe* bread = new Recipe("bread");
    const Recipe* ham = new Recipe("ham");
    const Recipe* oats = new Recipe("oats");
    const Recipe* corn = new Recipe("corn");


    assert(newList.getSize() == 0);
    assert(newList.isEmpty() == true);
    newList.append(bread);

    assert(newList.getSize() == 1);
    assert(newList.isEmpty() == false);

    newList.insert(ham, 0);
    newList.insert(oats, 2);
    newList.insert(corn, 1);
    assert(newList.getSize() == 4);
    // ham corn bread oats
    newList.print();
    assert(newList.removeIndex(2)->title == "bread");
    assert(newList.getSize() == 3);

    newList.clear();
    assert(newList.getSize() == 0);
    assert(newList.isEmpty() == true);

    // Delete Recipes to avoid memory leaks!
}

void RecipeListTestSize1() {
    RecipeList list;
    const Recipe* water = new Recipe("water");
    list.append(water);
    //list.removeIndex(1);
    const Recipe* milk = new Recipe("milk");
    list.append(milk);
    list.removeIndex(1);
    list.print();
}

Cookbook loadTestRecipies() {
    Cookbook cookbook;

    cookbook.addRecipe(new Recipe("Corn"));
    cookbook.addRecipe(new Recipe("pancake"));
    cookbook.addRecipe(new Recipe("waffle"));
    cookbook.addRecipe(new Recipe("water"));
    cookbook.addRecipe(new Recipe("bread"));
    cookbook.addRecipe(new Recipe("soup"));
    cookbook.addRecipe(new Recipe("salad"));
    cookbook.addRecipe(new Recipe("pasta"));
    cookbook.addRecipe(new Recipe("rice"));
    cookbook.addRecipe(new Recipe("steak"));
    cookbook.addRecipe(new Recipe("chicken"));
    cookbook.addRecipe(new Recipe("fish"));
    cookbook.addRecipe(new Recipe("burger"));
    cookbook.addRecipe(new Recipe("pizza"));
    cookbook.addRecipe(new Recipe("taco"));
    cookbook.addRecipe(new Recipe("sandwich"));
    cookbook.addRecipe(new Recipe("omelette"));
    cookbook.addRecipe(new Recipe("cake"));
    cookbook.addRecipe(new Recipe("pie"));

    return cookbook;
}
