#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <vector>


using namespace std;

class Book {
    string title;
    string author;
    string ISBN;
    bool availability;

    public:
        Book(string t, string a, string i, bool avail): title(t), author(a), ISBN(i), availability(avail) {}
        bool getAvailability() { return availability; }
        void setAvailability(bool a) {
            availability = a;
        }
        string getTitle() { return title; }
        string getAuthor() { return author; }
        string getISBN() { return ISBN; }
       
};

class User {
    protected:
        string name;
        int userID;
        vector<string> books;
    public:
        User(string n, int i): name(n), userID(i) {}

        string getName() { return name; }
        int getID() { return userID; }
        vector<string> getBooks() { return books; }
        string getBook(int i) { return books[i]; }
        void addBook(string b) { books.push_back(b); }
        void removeBook(int i) {
            books.erase(books.begin() + i);
        }
};

class Student : public User {
public:
    Student(string &n, int &i) : User(n, i) {}
};

class Faculty : public User {
public:
    Faculty(string &n, int &i) : User(n, i) {}
};

class Library {
    // Vector of pointers to dynamically allocated memory for the User class instances
    vector<unique_ptr<User>> users;
    // Vector of pointers to dynamically allocated memory for the Book class instances
    vector<unique_ptr<Book>> books;

    public:
        // Adding a new pointer to a new derived Student class to the vector with unique pointers to the User class instances
        void registerStudent(string n, int i) {
            users.push_back(make_unique<Student>(n, i));
          }
        // Adding a new pointer to a new derived Faculty class to the vector with unique pointers to the User class instances
        void registerFaculty(string n, int i) {
            users.push_back(make_unique<Student>(n, i));
        }
        // Adding instance of the Book class to the vector with unique pointers to these instances
        void addBook(string n, string a, string i) {
            // Looping through each pointer to each instance of Book classes in the books vector
            for (unique_ptr<Book> &book : books) {
                if (book->getISBN() == i) {
                    cout << "\nError, book could not be added at the moment, only adding one copy of a book is currently supported.\n";
                }
            }
            books.push_back(make_unique<Book>(n, a, i, true));
        }
        Book *searchBookTitle(string n) {
            for (unique_ptr<Book>& book : books) {
                if (book->getTitle() == n) {
                    return book.get();
                }
            }
            return nullptr;
        }
        Book* searchBookAuthor(string n) {
            for (unique_ptr<Book>& book : books) {
                if (book->getAuthor() == n) {
                    return book.get();
                }
            }
            return nullptr;
        }
        Book* searchBookISBN(string n) {
            for (unique_ptr<Book>& book : books) {
                if (book->getISBN() == n) {
                    return book.get();
                }
            }
            return nullptr;
        }
        User* searchUserID(int id) {
            for (unique_ptr<User>& user : users) {
                if (user->getID() == id) {
                    return user.get();
                }
            }
            return nullptr;
        }
};

