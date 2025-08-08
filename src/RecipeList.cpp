#include "RecipeList.h"
#include <iostream>
#include <stdexcept>

RecipeList::RecipeList() : head(nullptr),tail(nullptr) {}

RecipeList::~RecipeList(){
    clear();
}

void RecipeList::append(const Recipe &input){
    
    Node *tmp = new Node;
    tmp->data = input;
    if(head == nullptr){
        this->head = tmp;
        this->tail = tmp;
        ++this->size;
    }
    else {
        this->tail->next = tmp;
        tmp->prev = this->tail; 
        this->tail = tmp;
        ++this->size;
    }
}

void RecipeList::print() const{
    Node *tmp = head;
    while(tmp != nullptr){
        std::cout<<tmp->data.title<<std::endl;
        tmp = tmp->next;
    }
}

void RecipeList::clear() {
    Node *tmp = this->head;
    while(tmp != nullptr){
        Node *next = tmp->next;
        delete tmp;
        tmp = next;
    }
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
    
}

int RecipeList::getSize() const{
    return this->size;
}

Recipe RecipeList::getIndex(const int &index) const{
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    Node *tmp = nullptr;
    if((this->size / 2) < index){ //the index is past the halfway point, start at back and go backwards
        tmp = tail;
        for(int i = this->size - 1; i > index; --i){
            tmp = tmp->prev;
        }
    }
    else{ //start and beginning and go forwards
        tmp = head;
        for(int i = 0; i < index; ++i){
            tmp = tmp->next;
        }
    }
    return tmp->data;
}

Recipe RecipeList::removeIndex(const int &index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    Node *tmp = nullptr;
    if((this->size / 2) < index){ //the index is past the halfway point, start at back and go backwards
        tmp = tail;
        for(int i = this->size - 1; i > index; --i){
            tmp = tmp->prev;
        }
    }
    else{ //start and beginning and go forwards
        tmp = head;
        for(int i = 0; i < index; ++i){
            tmp = tmp->next;
        }
    }

    //remove node from list then delete node
    tmp->next->prev = tmp->prev;
    tmp->prev->next = tmp->next;
    tmp->next = nullptr;
    tmp->prev = nullptr;
    Recipe tmpRecipe = tmp->data;
    delete tmp;
    --this->size;
    return tmpRecipe;
}

void RecipeList::insert(const int &index, const Recipe &input) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    if (index - 1 == this->size) { //at end of list can just append
        this->append(input);
    }
    if (index == 0) {
        Node *newNode = new Node;
        newNode->data = input;
        newNode->next = this->head;
        this->head->prev = newNode;
        this->head = newNode;
        ++this->size;
    }
    Node *tmp = nullptr;
    if((this->size / 2) < index){ //the index is past the halfway point, start at back and go backwards
        tmp = tail;
        for(int i = this->size - 1; i > index; --i){
            tmp = tmp->prev;
        }
    }
    else{ //start and beginning and go forwards
        tmp = head;
        for(int i = 0; i < index; ++i){
            tmp = tmp->next;
        }
    }

    Node *newNode = new Node;
    newNode->data = input;
    //tie in new node
    tmp->prev->next = newNode;
    newNode->prev = tmp->prev;
    tmp->prev = newNode;
    newNode->next = tmp;
    ++this->size;
}

