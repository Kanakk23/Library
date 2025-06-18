#pragma once
#include <vector>
#include "user.hpp"
#include "book.hpp"

using namespace std;

class Faculty : public User
{
private:
    int fine;
    vector<string> book_history;
    // vector<Book *> books;
    vector<pair<Book *, time_t> > borrowedBooks;

public:
    // Constructors
    Faculty(string name, string id, string passowrd);
    // Getters and setters
    void showBooks();
    void showBooksHistory();
    void issue(Book *book);
    void display();
    void borrowBook(Book *book);
    void loadingBook(Book *book, time_t borrowTime);
    void returnBook(Book *book);
    int getFine();
    void setFine(int f) {fine = f;};
    vector<pair<Book *, time_t> >getIssuedBooks();
    vector<string> getBookHistory();
    void addHistoryBook(string isbn);
    void settleFine()
    {
        fine = 0;
    }
};