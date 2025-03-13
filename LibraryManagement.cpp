#include "LibraryManagement.h"
#include <string>

enum MenuOptions { ADD, REGISTER, SEARCH, BORROW, RETURN, EXIT };

enum BookSearchOptions { TITLE, AUTHOR, ISBN };



// Displays the main menu
void displayMainMenu() {
    cout << "Welcome to the Library:" << endl;
    cout << "1. Add Books" << endl;
    cout << "2. Register Users" << endl;
    cout << "3. Search for books" << endl;
    cout << "4. Borrow book" << endl;
    cout << "5. Return book" << endl;
    cout << "6. Exit" << endl;
}

// Displays the menu for book searches
void displayBookSearchMenu() {
    cout << "Select your preferred search option:" << endl;
    cout << "1. Title" << endl;
    cout << "2. Author" << endl;
    cout << "3. ISBN" << endl;
}

// Gets the menu options and validates it, given a max amount of menu options available
int getMenuOption(string option, int max) {
    bool menuValid;
    do {
        try {
            int userOption = stoi(option);
            if(userOption > 0 && userOption < max) {
                menuValid = true;
                return userOption;
            }
        } catch(const invalid_argument &e) {
            cin.clear();
            getline(cin, option);
        }
    } while(!menuValid);
    return 0;
}