// #include "student.hpp"
// #include <iostream>

// Student::Student(string name, string id, string password) : User(name, id, password, 's')
// {
//     fine = 0;
//     books.clear();
// }

// int Student::getFine()
// {
//     return fine;
// }

// void Student::showBooks()
// {
//     int index = 1;
//     for (Book *book : books)
//     {
//         cout << "Book " << index << ":" << endl;
//         book->display();
//         index++;
//     }
// }

// void Student::showBooksHistory()
// {
//     for (int i = 0; i < (this->book_history).size(); i++)
//     {
//         cout << (this->book_history)[i] << " ";
//     }
//     cout << endl;
// }

// void Student::issue(Book *book)
// {
//     borrowedBooks.push_back(book);
// }

// void Student::display()
// {
//     cout << "ID: " << id << "\nName: " << name
//          << "\nRole: " << role
//          << "\nFine: " << fine << endl;
//     cout << "Current Issued Books: ";
//     showBooks();
//     cout << "History of Issued Books: ";
//     showBooksHistory();
// }

// void Student::borrowBook(Book *book)
// {
//     if(fine > 0){
//         cout << "Cannot borrow books until fine is paid!\n";
//         return;
//     }
//     if (borrowedBooks.size() >= 3)
//         cout << "You have reached maximum limit for borrowing books!" << endl;
//         return;
//     if (book->getStatus() == 'b')
//         cout << "Book unavailable!" << endl;
//         return;

//     time_t now = time(0);
//     borrowedBooks.push_back(make_pair(book, now));
//     book->setStatus('b');
//     cout << "Book borrowed successfully!\n";
//     // this->books.push_back(book);
//     // book->setStatus('b');
//     // cout << "Succesfully borrowed the book!" << endl;

// }

// void Student::loadingBook(Book *book)
// {
//     this->books.push_back(book);
// }

// void Student::returnBook(Book *book)
// {
//     // Find the book in the books vector
//     auto it = find(books.begin(), books.end(), book);
//     if (it != books.end())
//     {
//         books.erase(it);                         // Remove the book from issued books
//         book_history.push_back(book->getIsbn()); // Store title in history
//         book->setStatus('a');                    // Mark book as available
//     }
//     else
//     {
//         cout << "Error: Book not found in issued books!\n";
//     }
// }

// vector<Book *> Student::getIssuedBooks() { return books; }
// vector<string> Student::getBookHistory() { return book_history; }

// void Student::addHistoryBook(string isbn)
// {
//     book_history.push_back(isbn);
// }

#include "student.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>

Student::Student(string name, string id, string password) : User(name, id, password, 's')
{
    fine = 0;
    borrowedBooks.clear();
}

int Student::getFine()
{
    return fine;
}

void Student::showBooks()
{
    int index = 1;
    for (auto &entry : borrowedBooks)
    {
        cout << "Book " << index << ":" << endl;
        entry.first->display();
        index++;
    }
}

void Student::showBooksHistory()
{
    for (const string &isbn : book_history)
    {
        cout << isbn << " ";
    }
    cout << endl;
}

void Student::issue(Book *book)
{
    time_t now = time(0);
    borrowedBooks.push_back(make_pair(book, now));
}

void Student::display()
{
    cout << "ID: " << id << "\nName: " << name
         << "\nRole: " << role
         << "\nFine: " << fine << endl;
    cout << "Current Issued Books: ";
    showBooks();
    cout << "History of Issued Books: ";
    showBooksHistory();
}

void Student::borrowBook(Book *book)
{
    if (fine > 0)
    {
        cout << "Cannot borrow books until fine is paid!\n";
        return;
    }
    if (borrowedBooks.size() >= 3)
    {
        cout << "You have reached the maximum limit for borrowing books!" << endl;
        return;
    }
    if (book->getStatus() == 'b')
    {
        cout << "Book unavailable!" << endl;
        return;
    }
    if(book->getStatus() == 'r')
    {
        cout << "Book is reserved, and can only be used inside of the library premise!" << endl;
        return;
    }
    bool overdue = false;
    for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it)
    {
        int daysLate = difftime(time(0), it->second) / (60); // using minutes as asked
        if (daysLate > 15)
        {
            cout << "You have the book (with isbn:"<< it->first->getIsbn() << ") which is issued for more than 15 days. Return it first to borrow more books!" << endl;
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

void Student::returnBook(Book *book)
{
    time_t now = time(0);
    for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it)
    {
        if (it->first == book)
        {
            double daysLate = difftime(now, it->second) / (60); // using minutes as asked
            if (daysLate > 15)
            {
                fine += (int)(daysLate - 15) * 10;
                cout << "Late return! Fine added: " << (int)(daysLate - 15) * 10 << " INR\n";
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

vector<pair<Book *, time_t> > Student::getIssuedBooks()
{
    return borrowedBooks;
}

vector<string> Student::getBookHistory()
{
    return book_history;
}

void Student::addHistoryBook(string isbn)
{
    book_history.push_back(isbn);
}

void Student::loadingBook(Book *book, time_t borrowTime)
{
    borrowedBooks.push_back(make_pair(book, borrowTime));
}
