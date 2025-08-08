//
// Created by jtmil on 8/8/2025.
//

#include "Cookbook.h"
#include <cctype>
#include <iostream>

Cookbook::Cookbook() {
    size = 0;
    for (char letter = 'A'; letter <= 'Z'; ++letter) {
        cookbook[letter] = RecipeList();
    }
}

void Cookbook::addRecipe(const Recipe &recipe) {
    if (!recipe.title.empty()) {
        const char firstLetter = std::toupper(recipe.title[0]);
        cookbook[firstLetter].append(recipe);
    }
    else {
        std::cout<<"Empty title"<<std::endl;
    }
}
