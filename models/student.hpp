#pragma once
#include "user.hpp"
#include "book.hpp"
#include <vector>

using namespace std;

class Student : public User
{
private:
    int fine;
    vector<string> book_history;
    vector<pair<Book *, time_t> > borrowedBooks;

    // vector<Book *> books;

public:
    // Constructors
    Student(string name, string id, string passowrd);
    // Getters and setters
    void showBooks();
    void showBooksHistory();
    void issue(Book *book);
    void display();
    void borrowBook(Book *book);
    void loadingBook(Book *book, time_t borrowTime);
    void returnBook(Book *book);
    void setFine(int f) { this->fine = f; };
    int getFine();
    vector<pair<Book *, time_t> > getIssuedBooks();
    vector<string> getBookHistory();
    void addHistoryBook(string isbn);
    void settleFine()
    {
        fine = 0;
    }
};