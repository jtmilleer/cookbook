//
// Created by jtmil on 8/8/2025.
//

#ifndef COOKBOOK_H
#define COOKBOOK_H

#include <map>
#include "RecipeList.h"
#include "Recipe.h"
#include <string>


class Cookbook {
public:
    Cookbook();
    //~Cookbook();

    void addRecipe(const Recipe &recipe);

    Recipe getRecipe(const std::string &recipe) const;

    const RecipeList &getLetter(const char &letter) const;

    void removeRecipe(const std::string &inputRecipe);

    int getRecipeCount() const;

    void print() const;

    // tags for Recipes





private:
    int size;
    std::map<char,RecipeList> cookbook;

    const int ALPHA_LIMIT = 30;
};



#endif //COOKBOOK_H
