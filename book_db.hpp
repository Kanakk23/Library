#pragma once
#include "models/book.hpp"
#include <vector>
#include <fstream>

using namespace std;

class BookDB
{
private:
    vector<Book> books;
    string filename;

public:
    BookDB();
    ~BookDB();
    void add(Book book);
    void remove(string ISBN);
    void update(Book book, string ISBN);
    void displayAll();
    vector<Book *> search(string keyword);
    void saveFile();
    void loadFile();
};