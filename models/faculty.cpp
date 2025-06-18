#include "faculty.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>

Faculty::Faculty(string name, string id, string password) : User(name, id, password, 'f')
{
    fine = 0;
    borrowedBooks.clear();
}

int Faculty::getFine()
{
    return fine;
}

void Faculty::showBooks()
{
    int index = 1;
    for (auto &entry : borrowedBooks)
    {
        cout << "Book " << index << ":" << endl;
        entry.first->display();
        index++;
    }
}

void Faculty::showBooksHistory()
{
    for (const string &isbn : book_history)
    {
        cout << isbn << " ";
    }
    cout << endl;
}

void Faculty::issue(Book *book)
{
    time_t now = time(0);
    borrowedBooks.push_back(make_pair(book, now));
}

void Faculty::display()
{
    cout << "ID: " << id << "\nName: " << name
         << "\nRole: " << role
         << "\nFine: " << fine << endl;
    cout << "Current Issued Books: ";
    showBooks();
    cout << "History of Issued Books: ";
    showBooksHistory();
}

void Faculty::borrowBook(Book *book)
{
    if (fine > 0)
    {
        cout << "Cannot borrow books until fine is paid!\n";
        return;
    }
    if (borrowedBooks.size() >= 5)
    {
        cout << "You have reached the maximum limit for borrowing books!" << endl;
        return;
    }
    if (book->getStatus() == 'b')
    {
        cout << "Book unavailable!" << endl;
        return;
    }
    if (book->getStatus() == 'r')
    {
        cout << "Book is reserved, and can only be used inside of the library premise!" << endl;
        return;
    }
    bool overdue = false;
    for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it)
    {
        
        int daysLate = difftime(time(0), it->second) / (60); // using minutes as asked
        if (daysLate > 60)
        {
            cout << "You have the book (with isbn:"<< it->first->getIsbn() << ") which is issued for more than 60 days. Return it first to borrow more books!" << endl;
            overdue = true;
        }
    }
    if (overdue)
        return;

    time_t now = time(0);
    borrowedBooks.push_back(make_pair(book, now));
    book->setStatus('b');
    cout << "Book borrowed successfully!\n";
}

void Faculty::returnBook(Book *book)
{
    time_t now = time(0);
    for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it)
    {
        if (it->first == book)
        {
            double daysLate = difftime(now, it->second) / (60);
            if (daysLate > 30)
            {
                // fine += (daysLate - 30) * 10;
                cout << "Late return! No worries!\n";
            }
            cout << "Book returned succefully!" << endl;
            borrowedBooks.erase(it);
            book_history.push_back(book->getIsbn());
            book->setStatus('a');
            return;
        }
    }
    cout << "Error: Book not found in borrowed books!\n";
}

vector<pair<Book *, time_t> > Faculty::getIssuedBooks()
{
    return borrowedBooks;
}

vector<string> Faculty::getBookHistory()
{
    return book_history;
}

void Faculty::addHistoryBook(string isbn)
{
    book_history.push_back(isbn);
}

void Faculty::loadingBook(Book *book, time_t borrowTime)
{
    borrowedBooks.push_back(make_pair(book, borrowTime));
}
