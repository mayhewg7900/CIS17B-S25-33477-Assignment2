#include "LibraryManagement.h"
#include <string>

bool validISBN(string s) {
    try {
        if(s.length() != 13) {
            cout << "Invalid ISBN length, please enter one that is 13 characters";
        }
        int i = stoi(s);
        return true;
    } 
    catch(const invalid_argument &e) {
        cout << "Error, please enter a valid number";
        return false;
    }
}