//
// Created by jtmil on 8/8/2025.
//

#include "RecipeList.h"
#include "Recipe.h"
#include <iostream>
#include <cassert>

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

int main() {
    RecipeListTest();
    return 0;
}