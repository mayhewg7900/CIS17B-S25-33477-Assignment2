#include "LibraryManagement.h"
#include <string>

enum MenuOptions { ADD, REGISTER, SEARCH, BORROW, RETURN, EXIT };

enum BookSearchOptions { TITLE, AUTHOR, ISBN };

bool validISBN(string s) {
    if(s.length() < 13) {
        cout << "Error, please enter an ISBN of valid length 13";
        return false;
    }
    else {
        return true;
    }
}

void displayMainMenu() {
    cout << "Welcome to the Library:" << endl;
    cout << "1. Add Books" << endl;
    cout << "2. Register Users" << endl;
    cout << "3. Search for books" << endl;
    cout << "4. Borrow book" << endl;
    cout << "5. Return book" << endl;
    cout << "5. Exit" << endl;
}

void displayBookSearchMenu() {
    cout << "Select your preferred search option:" << endl;
    cout << "1. Title" << endl;
    cout << "2. Author" << endl;
    cout << "3. ISBN" << endl;
}

int getMenuOption(int option, int max) {
    while(option < 1 || option > max) {
        cout << "\n Invalid menu option, please enter a choice of 1-6";
        cin >> option;
    }
    try {
        MenuOptions menuOption = MenuOptions(option);
        return menuOption;
    }
    catch(const invalid_argument &e) {
        cout << "Error, invalid menu option";
        return EXIT;
    }
}