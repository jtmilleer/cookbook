//
// Created by jtmil on 8/9/2025.
//


#include "Cookbook.h"
#include "Recipe.h"
#include "RecipeList.h"
#include <cassert>
#include <iostream>
#include <limits>
#include <curses.h>


void CookbookTest();

void RecipeListTest();

void RecipeListTestSize1();

void RecipeListTest2();

void B_EditTest();

Cookbook *loadTestRecipies();

void menuTest();

void menu();

void runMenu(Cookbook *testBook);

int main() {

    //menu();

    Cookbook *testBook = loadTestRecipies();

    runMenu(testBook);

    delete testBook;

    return 0;
}

void CookbookTest() {
    Cookbook cookbook;

    const Recipe* potato = new Recipe("potato");
    const Recipe* meatball = new Recipe("meatball");
    const Recipe* muffin = new Recipe("muffin");
    const Recipe* junebug = new Recipe("junebug");


    cookbook.addRecipe(potato);

    cookbook.addRecipe(meatball);
    cookbook.addRecipe(muffin);
    cookbook.addRecipe(junebug);


    cookbook.print();

    /*
    assert(cookbook.getRecipeCount() == 4);
    cookbook.getLetter('M').print();

    std::cout << cookbook.getRecipe("junebug")->title << std::endl;
    cookbook.removeRecipe("d");
    cookbook.removeRecipe("junebug");
    */

}

void RecipeListTest() {
    RecipeList newList;

    const Recipe* bread = new Recipe("bread");
    const Recipe* ham = new Recipe("ham");
    const Recipe* oats = new Recipe("oats");
    const Recipe* corn = new Recipe("corn");


    assert(newList.getSize() == 0);
    assert(newList.isEmpty() == true);
    newList.append(bread);

    assert(newList.getSize() == 1);
    assert(newList.isEmpty() == false);

    newList.insert(ham, 0);
    newList.insert(oats, 2);
    newList.insert(corn, 1);
    assert(newList.getSize() == 4);
    // ham corn bread oats
    newList.print();
    assert(newList.removeIndex(2)->title == "bread");
    assert(newList.getSize() == 3);

    newList.clear();
    assert(newList.getSize() == 0);
    assert(newList.isEmpty() == true);

    // Delete Recipes to avoid memory leaks!
}

void RecipeListTestSize1() {
    RecipeList list;
    const Recipe* water = new Recipe("water");
    list.append(water);
    //list.removeIndex(1);
    const Recipe* milk = new Recipe("milk");
    list.append(milk);
    list.removeIndex(1);
    list.print();
}

void RecipeListTest2() {
    RecipeList list;
    list.append(new Recipe("carrot"));
    list.append(new Recipe("cans"));
    list.removeIndex(0);
    list.print();

}

Cookbook *loadTestRecipies() {
    Cookbook *cookbook = new Cookbook;

    cookbook->addRecipe(new Recipe("Corn"));
    cookbook->addRecipe(new Recipe("pancake"));
    cookbook->addRecipe(new Recipe("waffle"));
    cookbook->addRecipe(new Recipe("water"));
    cookbook->addRecipe(new Recipe("bread"));
    cookbook->addRecipe(new Recipe("soup"));
    cookbook->addRecipe(new Recipe("salad"));
    cookbook->addRecipe(new Recipe("pasta"));
    cookbook->addRecipe(new Recipe("rice"));
    cookbook->addRecipe(new Recipe("steak"));
    cookbook->addRecipe(new Recipe("chicken"));
    cookbook->addRecipe(new Recipe("fish"));
    cookbook->addRecipe(new Recipe("burger"));
    cookbook->addRecipe(new Recipe("pizza"));
    cookbook->addRecipe(new Recipe("taco"));
    cookbook->addRecipe(new Recipe("sandwich"));
    cookbook->addRecipe(new Recipe("omelette"));
    cookbook->addRecipe(new Recipe("cake"));
    cookbook->addRecipe(new Recipe("pie"));
    cookbook->addRecipe(new Recipe("Junebug"));
    cookbook->addRecipe(new Recipe("Cosmo"));

    return cookbook;
}

void menuTest() {
    Cookbook *testBook = loadTestRecipies();
    int input = 0;
    while (true) {
        std::cout <<"\nEnter 1 to list the cookbook,\n"
                    "Enter 2 to add a recipe\n"
                    "Enter 3 to edit a letter\n"
                    "Enter 4 to exit\n"
                    "Input: ";

        if (!(std::cin >> input)) { //non int val
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout <<"Invalid input. Please enter a number.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (input == 1) {
            testBook->print();
            std::cout <<"\nPress Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (input == 2) {
            std::cout << "Enter a recipe name to add: ";
            std::string recipeInput;
            std::getline(std::cin, recipeInput);
            if (!recipeInput.empty()) {
                testBook->addRecipe(new Recipe(recipeInput));
                std::cout <<"Recipe added.\n";
            } else {
                std::cout <<"Recipe name cannot be empty.\n";
            }
        }
        else if (input == 3) {
            std::cout<<"Enter a character to edit"<<std::endl;
            char input;
            std::cin>>input;
            testBook->editLetter(input);
        }
        else if (input == 4) {
            std::cout <<"Exiting...\n";
            delete testBook;
            break;
        }
        else {
            std::cout <<"Not a valid option.\n";
        }
    }
}

void menu() {
    Cookbook *testBook = loadTestRecipies();

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    scrollok(stdscr, TRUE); //enable scrolling

    int ch = 0;
    std::string feedback;

    // Print menu at the top once
    int menuRow = 0;
    move(menuRow++, 0);
    printw("Welcome to my cookbook!");
    move(menuRow++, 0);
    printw("1. List Cookbook");
    move(menuRow++, 0);
    printw("2. Add a Recipe");
    move(menuRow++, 0);
    printw("3. Edit a Letter");
    move(menuRow++, 0);
    printw("4. Exit");
    refresh();

    // Start printing cookbook below the menu
    int nextRow = menuRow + 1;

    while (ch != '4') {
        // Print feedback below the last printed cookbook
        move(nextRow++, 0); // move to next row for feedback
        clrtoeol();
        printw("%s", feedback.c_str());
        refresh();

        ch = getch(); // wait for input

        if (ch == '1') {
            // Print cookbook starting from nextRow
            testBook->viewCookbookCursor(); // returns row after last line printed
            //feedback = "Cookbook printed above.";
        }
        else if (ch == '2') feedback = "You pressed 2 to insert";
        else if (ch == '3') feedback = "You pressed 3 to edit";
        else if (ch != '4') feedback = "You pressed something else!";
    }

    endwin();
    delete testBook;
}

void runMenu(Cookbook* testBook) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int ch = 0;
    std::string feedback;

    while (ch != '4') {
        clear(); // always start fresh

        // Print menu
        int menuRow = 0;
        mvprintw(menuRow++, 0, "Welcome to my cookbook!");
        mvprintw(menuRow++, 0, "1. View Cookbook");
        mvprintw(menuRow++, 0, "2. Add a Recipe");
        mvprintw(menuRow++, 0, "3. Edit a Letter");
        mvprintw(menuRow++, 0, "4. Exit");

        // Show feedback (if any) below menu
        if (!feedback.empty()) {
            mvprintw(menuRow + 1, 0, "%s", feedback.c_str());
        }

        refresh();

        ch = getch();

        if (ch == '1') {
            testBook->viewCookbookCursor(); // waits for ENTER inside
            feedback = "Cookbook viewed.";
        }
        else if (ch == '2') {
            testBook->editLetterCursor();
            feedback = "You pressed 2 to insert";
        }
        else if (ch == '3') {
            feedback = "You pressed 3 to edit";
        }
        else if (ch != '4') {
            feedback = "Invalid choice!";
        }
    }

    endwin();
}