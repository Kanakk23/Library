#pragma once
#include <string>
#include <iostream>
#include <map>
#include <chrono>
#include <ctime>

using namespace std;

class User
{
protected:
    string id;
    string name;
    string password;
    char role;

public:
    // Constructors
    // User();
    User(string name, string password, char role);
    User(string name, string id, string password, char role);
    virtual ~User();
    // Getters and Setters
    void setName(string name);
    void setId(string id);
    void setPassword(string password);
    void setRole(char role);
    string getName();
    string getId();
    string getPassword();
    char getRole();
    virtual void display() = 0;
    virtual void borrowBook(class Book *book) = 0;
    virtual void returnBook(class Book *book) = 0;
    virtual void loadingBook(class Book *book, time_t borrowTime) = 0;
    virtual int getFine() = 0;
    virtual vector<pair<Book *, time_t> >getIssuedBooks() = 0;
    virtual vector<string> getBookHistory() = 0;
    virtual void addHistoryBook(string isbn) = 0;
    virtual void settleFine() = 0;
    virtual void setFine(int f) {};
};
