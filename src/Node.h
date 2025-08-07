#ifndef NODE_H
#define NODE_H

#include "Recipe.h"

struct Node{
    Recipe data;
    Node *next = nullptr;
    Node *prev = nullptr;
};

#endif 