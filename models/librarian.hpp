#pragma once
#include <vector>
#include "user.hpp"
#include "book.hpp"

using namespace std;

class Librarian : public User
{
private:
public:
    // Constructors
    Librarian(string name, string id, string passowrd) : User(name, id, passowrd, 'l') {}
    // Getters and setters
    void display() {};
    void borrowBook(class Book *book) {};
    void returnBook(class Book *book) {};
    void loadingBook(Book *book, time_t borrowTime) {};
    int getFine() { return 0; };
    vector<pair<Book *, time_t> > getIssuedBooks() { return vector<pair<Book *, time_t> >(); } // Return an empty vector instead of NULL
    vector<string> getBookHistory() { return vector<string>(); }
    void addHistoryBook(string isbn) {};
    void settleFine() {};
};