#include "LibraryManagement.h"
#include <string>

bool validISBN(string s) {
    if(s.length() < 13) {
        cout << "Error, please enter an ISBN of valid length 13";
        return true;
    }
    else {
        return false;
    }
}

enum MenuOptions { ADD, REGISTER, SEARCH, BORROW, RETURN, EXIT};

void displayMainMenu() {
    cout << "Welcome to the Library:" << endl;
    cout << "1. Add Books" << endl;
    cout << "2. Register Users" << endl;
    cout << "3. Search for books" << endl;
    cout << "4. Borrow book" << endl;
    cout << "5. Return book" << endl;
    cout << "5. Exit" << endl;
}

int getMenuOption(int option) {
    while(option < 1 || option > 10) {
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