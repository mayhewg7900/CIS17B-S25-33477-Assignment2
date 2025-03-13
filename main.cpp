#include "LibraryManagement.cpp"

int main() {

    // Library object, dynamically manages the users and books, as well as handles searching
    Library library;

    // Enumerator for main menu options
    MenuOptions mainOption;
    // Enumerator for book search menu options
    BookSearchOptions searchOption;
    
    // Stores the currently entered book's name, author, and ISBN
    string bookName;
    string bookAuthor;
    string bookISBN;

    // Stores the current menu option chosen
    string menuOption;
    int option;

    // Stores the current userID and name
    int userID;
    string userName;

    // Points to the Book object
    Book *bookPtr = nullptr;
    // Points to the User object, including its derivations
    User *userPtr = nullptr;
    
    // Stores the current ID, iterated on when a new user is added
    int id = 0;

    // Do...
    do {
        // Display the menu
        displayMainMenu();
        // Get the menu option
        cin >> menuOption;
        // Validate the menu option
        option = getMenuOption(menuOption,7);
        // Cast the menu option to type MenuOptions
        mainOption = MenuOptions(option - 1);
        // If user choice is...
        switch(mainOption) {
            case ADD:
                cout << "Please enter the book name: ";
                cin.ignore();
                getline(cin, bookName);
                cout << "Please enter the book author: ";
                getline(cin, bookAuthor);
                cout << "Please enter the ISBN: ";
                cin >> bookISBN;
                // While ISBN length is not 13...
                while(bookISBN.length() != 13) {
                    cout << "Invalid ISBN length, please enter an ISBN of length 13: ";
                    cin >> bookISBN;
                }
                library.addBook(bookName, bookAuthor, bookISBN);
                break;
            case REGISTER:
                cout << "Are you student or faculty? 1 for faculty, 2 for student: ";
                cin >> menuOption;
                cin.ignore();
                // If the choice was faculty...
                option = getMenuOption(menuOption,2);
                if(option-1) {
                    cout << "Enter your name: ";
                    cin >> userName;
                    library.registerFaculty(userName, id);
                    cout << "Successfully registered faculty " << userName << " with ID number:" << id << endl;
                    id++;
                }
                // Else the choice was student
                else {
                    cout << "Enter your name: ";
                    cin >> userName;
                    library.registerStudent(userName, id);
                    cout << "Successfully registered student " << userName << " with ID number:" << id << endl;
                    id++;
                }
                break;
            case SEARCH:
                // Display the search menu
                displayBookSearchMenu();
                cin >> menuOption;
                option = getMenuOption(menuOption,3);
                searchOption = BookSearchOptions(option-1);
                // If search option is...
                switch(searchOption) {
                    case TITLE:
                        cout << "Please enter the title: ";
                        cin.ignore();
                        getline(cin, bookName);
                        bookPtr = library.searchBookTitle(bookName);
                        // If there is a valid book...
                        if(bookPtr) {
                            cout << bookPtr->getTitle()  << " has been found!" << endl;
                            // If the book is available...
                            if(bookPtr->getAvailability()) {
                                "\nThis book is available for checkout!\n";
                            }
                            else {
                                "\nThis book is not available for checkout!\n";
                            }
                        }
                        else {
                            cout << "\nBook could not be found! Please try again!\n";
                        }
                        break;

                    case AUTHOR:
                        cout << "Please enter the author: ";
                        cin.ignore();
                        getline(cin, bookName);
                        cin >> bookAuthor;
                        bookPtr = library.searchBookAuthor(bookAuthor);
                        // If there is a valid book...
                        if(bookPtr != nullptr) {
                            cout << bookPtr->getAuthor() << " has been found!" << endl;
                            cout << "The author wrote the book: " << bookPtr->getTitle() << endl;
                            // If the book is available...
                            if(bookPtr->getAvailability()) {
                                "\nThis book is available for checkout!\n";
                            }
                            else {
                                "\nThis book is not available for checkout!\n";
                            }
                        }
                        break;

                    case ISBN:
                        cout << "Please enter the ISBN: ";
                        cin >> bookISBN;
                        bookPtr = library.searchBookISBN(bookISBN);
                        // If there is a valid book...
                        if(bookPtr != nullptr) {
                            cout << bookPtr->getTitle() << " has been found by " << bookPtr->getAuthor() << endl;
                            // If the book is available...
                            if(bookPtr->getAvailability()) {
                                cout << "\nThis book is available for checkout!\n";
                            }
                            else {
                                "\nThis book is not available for checkout!\n";
                            }
                            }
                        else {
                            cout << "Book could not be found! Returning to the main menu.";
                        }
                        break;
                    }
                    break;

            case BORROW:
                cout << "Please enter the ISBN of the book you would like to checkout: ";
                cin >> bookISBN;
                bookPtr = library.searchBookISBN(bookISBN);
                if(bookPtr != nullptr) {
                    // If the book is available...
                    if(bookPtr->getAvailability()) {
                        cout << bookPtr->getTitle() << " is available for checkout! Press 1 to check out, or 2 to cancel" << endl;
                        cin >> option;
                        // If the user wants to check out...
                        if(option == 1) {
                            cout << "Please enter your ID: ";
                            cin >> userID;
                            userPtr = library.searchUserID(userID);
                            if(userPtr == nullptr) {
                                cout << "Invalid user ID, returning to the main menu" << endl;
                            }
                            else {
                                userPtr->addBook(bookPtr->getISBN());
                                bookPtr->setAvailability(false);
                                cout << userPtr->getName() << " has successfully checked out " << bookPtr->getTitle() << endl;
                            }
                        }
                        // If the user wants to cancel...
                        else if(option == 2) {
                            cout << "Returning to the main menu..." << endl;
                        }
                        // Else, option is invalid, return to the menu
                        else {
                            cout << "Invalid option, returning to the main menu..." << endl;
                        }
                    }
                    // Else, book is not available for check out
                    else {
                        cout << bookPtr->getTitle() << " is not available for checkout right now! Please check again later!" << endl;
                    }
                }
                // Else, ISBN entered was invalid
                else {
                    cout << "ISBN is invalid, returning to the main menu";
                }
                break;

            case RETURN:
                cout << "Please enter your user ID: ";
                cin >> userID;
                userPtr = library.searchUserID(userID);
                // If user exists...
                if(userPtr) {
                    cout << "Hello " << userPtr->getName() << endl;
                    int i = 0;
                    // For each book in the user's books, display the ones checked out
                    for(string book : userPtr->getBooks()) {
                        i++;
                        cout << i << ". " << book << endl;
                    }
                    // If the user has books checked out
                    if (i) {
                        cout << "Please select the book you were like to return by entering the number next to it (1 - " << i << "):";
                        int userBookReturn;
                        cin >> userBookReturn;
                        // If the user book selection is invalid...
                        if(userBookReturn <= 0 || userBookReturn > i) {
                            cout << "Invalid book selection, returning to the main menu." << endl;
                        }
                        // Else find the book, remove it from the user's book list, and set it to being available
                        else {
                            bookPtr = library.searchBookISBN(userPtr->getBook(i-1));
                            userPtr->removeBook(userBookReturn - 1);
                            if(bookPtr) {
                                bookPtr->setAvailability(true);
                            }
                            cout << "The book has successfully been checked in!" << endl;
                        }
                    }
                    // Else the user has no books checked out
                    else {
                        cout << "You have no books checked out right now! Returning to the main menu..." << endl;
                    }
                }
                // Else the user ID does not exist
                else {
                    cout << "User ID does not exist, returning to the main menu..." << endl;
                }
                break;
            case EXIT:
                cout << "Exiting the application...";
                break;
        }
    } while(mainOption != EXIT);
}