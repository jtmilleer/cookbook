//
// Created by jtmil on 8/8/2025.
//

#ifndef COOKBOOK_H
#define COOKBOOK_H

#include <unordered_map>
#include "RecipeList.h"
#include "Recipe.h"
#include <string>


class Cookbook {
public:
    Cookbook();
    //~Cookbook();

    void addRecipe(const Recipe &recipe);

    Recipe getRecipe(const std::string &recipe) const;

    RecipeList getLetter(const char &letter) const;

    void removeRecipe(const std::string &recipe);



private:
    int size;
    std::unordered_map<char,RecipeList> cookbook;
};



#endif //COOKBOOK_H
