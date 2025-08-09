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

int main() {


    CookbookTest();


    return 0;
}

void CookbookTest() {
    Cookbook cookbook;

    Recipe potato;
    potato.title = "potato";

    Recipe meatball;
    meatball.title = "meatball";

    Recipe muffin;
    muffin.title = "muffin";

    Recipe junebug;
    junebug.title = "junebug";

    cookbook.addRecipe(potato);
    cookbook.addRecipe(meatball);
    cookbook.addRecipe(muffin);
    cookbook.addRecipe(junebug);

    cookbook.print();

    assert(cookbook.getRecipeCount() == 4);
    cookbook.getLetter('M').print();

    std::cout<<cookbook.getRecipe("junebug").title<<std::endl;
    cookbook.removeRecipe("d");
    cookbook.removeRecipe("junebug");



}


void RecipeListTest() {
    RecipeList newList;

    Recipe bread;
    bread.title = "bread";


    Recipe ham;
    ham.title = "ham";

    Recipe oats;
    oats.title = "oats";

    Recipe corn;
    corn.title = "corn";



    assert(newList.getSize() == 0);
    assert(newList.isEmpty() == true);
    newList.append(bread);

    assert(newList.getSize() == 1);
    assert(newList.isEmpty() == false);

    newList.insert(ham,0);
    newList.insert(oats,2);
    newList.insert(corn,1);
    assert(newList.getSize() == 4);
    //ham corn bread oats
    newList.print();
    assert(newList.removeIndex(2).title == "bread");
    assert(newList.getSize() == 3);

    newList.clear();
    assert(newList.getSize() == 0);
    assert(newList.isEmpty() == true);





}

void RecipeListTestSize1() {
    RecipeList list;
    Recipe water;
    water.title = "water";
    list.append(water);
    //list.removeIndex(1);
    Recipe milk;
    milk.title = "milk";
    list.append(milk);
    list.removeIndex(1);
    list.print();
}


