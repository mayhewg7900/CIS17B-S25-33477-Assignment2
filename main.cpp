#include "LibraryManagement.cpp"

int main() {
    Library library;
    MenuOptions option;
    int studentOrFaculty;
    string bookName;
    string bookAuthor;
    string ISBN;
    int menuOption;
    string s;
    int id = 0;
    do {
        displayMainMenu();
        cin >> menuOption;
        menuOption = getMenuOption(menuOption);
        option = MenuOptions(menuOption-1);
        switch(option) {
            case ADD:
                cout << "Please enter the book name: ";
                cin >> bookName;
                cout << "Please enter the book author: ";
                cin >> bookAuthor;
                cout << "Please enter the ISBN: ";
                cin >> ISBN;
                while(!validISBN(ISBN)) {
                    cin >> ISBN;
                }
                library.addBook(bookName, bookAuthor, ISBN);
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
        }
    } while(option != EXIT);
}