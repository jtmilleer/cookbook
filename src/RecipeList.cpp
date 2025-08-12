#include "RecipeList.h"
#include <iostream>
#include <stdexcept>

RecipeList::RecipeList() : head(nullptr),tail(nullptr),size(0) {}

RecipeList::~RecipeList(){
    clear();
}

void RecipeList::append(const Recipe *input){
    
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
        const Node *tmp = head;
        std::cout<<"Head: "<<tmp<<" Data: "<<tmp->data<<std::endl;
        while(tmp != nullptr){
            //std::cout<<"Printing "<<tmp<<std::endl;
            if (tmp->next!=nullptr) {
                std::cout<<"Hi from list print inside last checker"<<std::endl;
                std::cout<<tmp->data->title+",";
            }
            else {
                std::cout<<tmp->data->title<<std::endl;
            }
            tmp = tmp->next;
        }
    }

void RecipeList::clear() {
    Node *tmp = this->head;
    while(tmp != nullptr){
        Node *next = tmp->next;
        tmp->next = nullptr;
        tmp->prev = nullptr;
        delete tmp->data;
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

const Recipe* RecipeList::getIndex(const int &index) const{
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

const Recipe* RecipeList::removeIndex(const int &index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    if (index == 0) { //removing beginning of list
        Node *tmp = this->head;
        const Recipe *tmpRecipe = tmp->data;
        this->head = this->head->next;

        delete tmp;
        --this->size;
        if (this->size == 0) {
            this->tail = nullptr;
        }
        else {
            this->head->prev = nullptr;
        }
        return tmpRecipe;
    }
    if (index == this->size - 1) { //removing end of list
        Node *tmp = this->tail;
        const Recipe *tmpRecipe = tmp->data;
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
        delete tmp;
        --this->size;
        return tmpRecipe;
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
    const Recipe *tmpRecipe = tmp->data;
    delete tmp;
    --this->size;
    return tmpRecipe;
}

void RecipeList::removeRecipeStr(const std::string &input) {
    Node *tmp = this->head;
    Node *prev = nullptr;
    while (tmp != nullptr && tmp->data->title != input) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == nullptr) {
        std::cout << "Recipe not found.\n";
        return;
    }
    std::cout<<"Trying to remove node "<<tmp<<" with val "<<tmp->data->title<<std::endl;

    //This causes a bad_alloc, doesn't remove head right
    if (prev == nullptr) {
        this->head = tmp->next;
    } else {
        prev->next = tmp->next;
    }

    if (tmp == this->tail) {
        this->tail = prev;
    }

    delete tmp->data;
    delete tmp;
    --this->size;

}


void RecipeList::insert(const Recipe *input, const int &index) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of range");
    }
    if (index == this->size) { //at end of list can just append
        this->append(input);
    }
    else if (index == 0) {
        Node *newNode = new Node;
        newNode->data = input;
        newNode->next = this->head;
        this->head->prev = newNode;
        this->head = newNode;
        ++this->size;
    }
    else {
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
}

bool RecipeList::isEmpty() const {
    return this->size == 0;
}


