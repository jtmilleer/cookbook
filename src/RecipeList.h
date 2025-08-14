#ifndef RECIPELIST_H
#define RECIPELIST_H

#include "Node.h"
#include "Recipe.h"

class RecipeList{
private:
    Node *head;
    Node *tail;
    int size;
public:
    RecipeList();
    ~RecipeList();

    void append(const Recipe *input);
    void print() const;
    void clear();
    int getSize() const;
    const Recipe *getIndex(const int &index) const;
    const Recipe *removeIndex(const int &index);
    void removeRecipeStr(const std::string &input);
    void insert(const Recipe *input, const int &index );
    bool isEmpty() const;
    void printCursor() const;




};

#endif