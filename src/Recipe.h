#ifndef RECIPE_H
#define RECIPE_H

#include <string>

struct Recipe{
    std::string title;
    std::string ingredients;
    std::string instructions;

    Recipe(const std::string &inputTitle): title(inputTitle){};
};

#endif 