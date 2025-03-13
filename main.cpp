#include "LibraryManagement.cpp"

int main() {
    Library library;
    MenuOptions mainOption;
    BookSearchOptions searchOption;
    int studentOrFaculty;
    string bookName;
    string bookAuthor;
    string bookISBN;
    int menuOption;
    int userID;
    Book *bookPtr = nullptr;
    User *userPtr = nullptr;
    string s;
    int id = 0;
    do {
        displayMainMenu();
        cin >> menuOption;
        menuOption = getMenuOption(menuOption,7);
         mainOption = MenuOptions(menuOption-1);
        switch(mainOption) {
            case ADD:
                cout << "Please enter the book name: ";
                cin >> bookName;
                cout << "Please enter the book author: ";
                cin >> bookAuthor;
                cout << "Please enter the ISBN: ";
                cin >> bookISBN;
                while(bookISBN.length() <= 12) {
                    cin >> bookISBN;
                }
                library.addBook(bookName, bookAuthor, bookISBN);
                break;
            case REGISTER:
                cout << "Are you student or faculty? 1 for student, 2 for faculty.";
                cin >> studentOrFaculty;
                while(studentOrFaculty != 1 && studentOrFaculty != 2) {
                    cout << "Sorry that input is invalid, please input 1 or 2" << endl;
                    cin >> studentOrFaculty;
                }
                if(studentOrFaculty - 1) {
                    cout << "Enter your name: ";
                    cin >> s;
                    library.registerFaculty(s, id);
                    cout << "Successfully registered student " << s << " with ID number: " << id;
                    id++;
                }
                else {
                    cout << "Enter your name: ";
                    cin >> s;
                    library.registerStudent(s, id);
                    cout << "Successfully registered student " << s << " with ID number: " << id;
                    id++;
                }
                break;
            case SEARCH:
                displayBookSearchMenu();
                cin >> menuOption;
                menuOption = getMenuOption(menuOption,3);
                searchOption = BookSearchOptions(menuOption-1);
                switch(searchOption) {
                    case TITLE:
                        cout << "Please enter the title: ";
                        cin >> bookName;
                        bookPtr = library.searchBookTitle(bookName);
                        if(bookPtr != nullptr) {
                            cout << bookPtr->getTitle()  << " has been found!";
                        }
                        else {
                            cout << "\nBook could not be found! Please try again!\n";
                        }
                        break;
                    case AUTHOR:
                        cout << "Please enter the author: ";
                        cin >> bookAuthor;
                        bookPtr = library.searchBookAuthor(bookAuthor);
                        if(bookPtr != nullptr) {
                            cout << bookPtr->getAuthor() << " has been found!" << endl;
                            cout << "The author wrote the book: " << bookPtr->getTitle() << endl;
                            if(bookPtr->getAvailability()) {
                                "\nThis book is available for checkout!\n";
                            }
                            else {
                                "\nThis book is not available for checkout!\n";
                            }
                        }
                    case ISBN:
                        cout << "Please enter the ISBN: ";
                        cin >> bookISBN;
                        bookPtr = library.searchBookISBN(bookISBN);
                        if(bookPtr != nullptr) {
                            cout << bookPtr->getTitle() << " has been found by " << bookPtr->getAuthor() << endl;
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
                case BORROW:
                    bool availability;
                    cout << "Please enter the ISBN of the book you would like to checkout: ";
                    cin >> bookISBN;
                    bookPtr = library.searchBookISBN(bookISBN);
                    if(bookPtr != nullptr) {
                        availability = bookPtr->getAvailability();
                        if(availability) {
                            cout << bookPtr->getTitle() << " is available for checkout! Press 1 to check out, or 2 to cancel" << endl;
                            cin >> menuOption;
                            if(menuOption == 1) {
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
                        }
                        else {
                            cout << bookPtr->getTitle() << " is not available for checkout right now! Please check again later!" << endl;
                        }
                    }
                    else {
                        cout << "ISBN is invalid, returning to the main menu";
                    }
                    break;

                case RETURN:
                    cout << "Please enter your user ID: ";
                    cin >> userID;
                    userPtr = library.searchUserID(userID);
                    if(userPtr != nullptr) {
                        cout << "We have found the books you have checked out: " << endl;
                        int i = 0;
                        for(string book : userPtr->getBooks()) {
                            i++;
                            cout << i << ". " << book << endl;
                        }
                        if (i) {
                            cout << "Please select the book you were like to return by entering the number next to it (1 - " << i << "):";
                            int userBookReturn;
                            cin >> userBookReturn;
                            if(userBookReturn <= 0 || userBookReturn > i) {
                                cout << "Invalid book selection, returning to the main menu." << endl;
                            }
                            else {
                                bookPtr = library.searchBookISBN(userPtr->getBook(i-1));
                                userPtr->removeBook(userBookReturn - 1);
                                if(bookPtr) {
                                    bookPtr->setAvailability(true);
                                }
                                cout << "The book has successfully been checked in!" << endl;
                            }
                        }


                    }

        }
    } while(mainOption != EXIT);
}