#include "book_db.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

BookDB::BookDB()
{
    filename = "books_data.txt";
    loadFile();
}
BookDB::~BookDB()
{
    filename = "books_data.txt";
    saveFile();
}

void BookDB::add(Book book)
{
    books.push_back(book);
}

void BookDB::remove(string ISBN)
{
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getIsbn() == ISBN)
        {
            books.erase(books.begin() + i);
        }
    }
}

void BookDB::update(Book book, string ISBN)
{
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getIsbn() == ISBN)
        {
            books[i] = book;
        }
    }
}

void BookDB::displayAll()
{
    for (int i = 0; i < books.size(); i++)
    {
        cout << "Book " << i + 1 << ":" << endl;
        books[i].display();
    }
}

vector<Book *> BookDB::search(string keyword)
{
    vector<Book *> result;

    if (!keyword.empty())
    {
        // Search by ISBN
        for (Book &book : books)
        {
            if (book.getIsbn() == keyword)
                result.push_back(&book);
        }

        // Search by Title
        for (Book &book : books)
        {
            if (book.getTitle().find(keyword) != string::npos)
                result.push_back(&book);
        }

        // Search by Author
        for (Book &book : books)
        {
            if (book.getAuthor().find(keyword) != string::npos)
                result.push_back(&book);
        }

        // Search by Publisher
        for (Book &book : books)
        {
            if (book.getPublisher().find(keyword) != string::npos)
                result.push_back(&book);
        }
    }

    return result;
}

// Save books to file
void BookDB::saveFile()
{
    ofstream file(filename, ios::trunc);
    if (!file)
    {
        cerr << "Error: Unable to open file for writing!\n";
        return;
    }

    for (int i = 0; i < books.size(); i++)
    {
        file << books[i].getIsbn() << "|"
             << books[i].getTitle() << "|"
             << books[i].getAuthor() << "|"
             << books[i].getPublisher() << "|"
             << books[i].getYear() << "|"
             << books[i].getStatus() << "\n";
    }

    file.close();
}

// Load books from file
void BookDB::loadFile()
{
    books.clear();
    ifstream file(filename);
    if (!file)
    {
        cerr << "Warning: No existing book data found. Creating new database.\n";
        return;
    }

    string title, author, isbn, publisher;
    char status;
    int year;

    while (getline(file, isbn, '|') &&
           getline(file, title, '|') &&
           getline(file, author, '|') &&
           getline(file, publisher, '|') &&
           (file >> year) &&
           file.ignore(1, '|') && // Ignore '|' before reading status
           (file >> status) &&    // Read status as a char
           file.ignore(1, '\n'))  // Ignore the newline at the end of the line
    {
        books.emplace_back(title, author, isbn, publisher, year, status);
    }

    file.close();
}
