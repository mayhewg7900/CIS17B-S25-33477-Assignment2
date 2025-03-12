#include <iostream>
#include <string>
#include <cctype>

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
};

class User {
    protected:
        string name;
        int userID;
    public:
        User(string n, int i): name(n), userID(i) {}

        string getName() { return name; }
        int getID() { return userID; }
};

class Library {
    
};

class Student : User {
    public:
        Student(string n, int i): User(n, i) {}
};

class Faculty : User {
    public:
        Faculty(string n, int i): User(n, i) {}
};