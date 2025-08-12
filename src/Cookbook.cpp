//
// Created by jtmil on 8/8/2025.
//

#include "Cookbook.h"
#include <cctype>
#include <iostream>

Cookbook::Cookbook() {
    size = 0;
    //for (char letter = 'A'; letter <= 'Z'; ++letter) {
       // cookbook[letter] = RecipeList();
    //}
}

void Cookbook::addRecipe(const Recipe *recipe) {
    if (!recipe->title.empty()) {
        const char firstLetter = std::toupper(recipe->title[0]);
        if (cookbook[firstLetter].getSize() >= ALPHA_LIMIT) {
            std::cout<<"Letter at it's limit, please remove a recipe"<<std::endl;
        }
        else {
            cookbook[firstLetter].append(recipe);
            ++this->size;
        }

    }
    else {
        std::cout<<"Empty title"<<std::endl;
    }
}

const Recipe* Cookbook::getRecipe(const std::string &inputRecipe) const {
    const char firstLetter = std::toupper(inputRecipe[0]);
    const RecipeList &letterList = cookbook.at(firstLetter);
    for (int i = 0; i < letterList.getSize(); ++i) {
        if (letterList.getIndex(i)->title == inputRecipe) {
            return letterList.getIndex(i);
        }
    }
    throw std::runtime_error("Recipe not found");
}

const RecipeList *Cookbook::getLetter(const char &letter) const {
    return &cookbook.at(std::toupper(letter));
}

void Cookbook::editLetter(const char &letter) {
    RecipeList letterList;
    try {
        letterList = this->cookbook.at(std::toupper(letter));
    }
    catch (const std::out_of_range &e){
        std::cout<<"Letter not found in cookbook"<<std::endl;
        return;
    }
    std::cout<<"Trying to edit list "<<&letterList<<" with size "<<letterList.getSize()<<" letter: "<<letter<<std::endl;
    letterList.print();
    std::cout<<"Enter what recipe you would like to remove"<<std::endl;
    std::string input;
    std::cin.ignore();
    std::getline(std::cin,input);
    letterList.removeRecipeStr(input);

}


void Cookbook::removeRecipe(const std::string &inputRecipe) {
    const char firstLetter = std::toupper(inputRecipe[0]);
    RecipeList &letterList = cookbook.at(firstLetter);
    int removalCount = 0;
    int i = 0;
    while (i < letterList.getSize()) {
        const std::string title = letterList.getIndex(i)->title;
        if (title == inputRecipe) {
            letterList.removeIndex(i);
            ++removalCount;
        }
        else {
            ++i;
        }
    }
    std::cout<<"Removed " << removalCount <<" instances of " << inputRecipe<<std::endl;
}

int Cookbook::getRecipeCount() const {
    return this->size;
}

void Cookbook::print() const {
    //this line was casuing segfault, std::map<char,RecipeList> internally stores the chars as const char?
    //so this was copying and causing a deletion of already freed memory
    for (const std::pair<const char, RecipeList>& pair :this->cookbook) {
        if (!pair.second.isEmpty()) {
            //std::cout<<"Printing "<<&pair.second<<std::endl;
            std::cout<<pair.first<<": ";
            pair.second.print();
        }

    }

}
