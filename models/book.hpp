#pragma once
#include "user.hpp"
#include <string>
using namespace std;

class Book
{
private:
    string title;
    string author;
    string publisher;
    int year;
    string isbn;
    char status;

public:
    // Constructor
    Book(string title, string author, string isbn, string publisher, int year, char status);
    // Getters and Setters
    void setTitle(string title);
    void setAuthor(string author);
    void setIsbn(string isbn);
    void setPublisher(string publisher);
    void setYear(int year);
    void setStatus(char status);
    char getStatus();
    string getTitle();
    string getAuthor();
    string getIsbn();
    string getPublisher();
    int getYear();

    void display();
};
