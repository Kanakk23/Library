// #include "book_db.hpp"
// #include "user_db.hpp"
// #include "models/student.hpp"
// #include "models/faculty.hpp"
// #include "models/librarian.hpp"
// #include <iostream>

// using namespace std;

// void studentFacultyMenu(User *user, BookDB &bookDB)
// {
//     while (true)
//     {
//         cout << "\n1. View all books\n2. Search for a book\n3. Borrow a book\n4. Return a book\n5. Get fine amount\n6. Settle fine\n7. Logout\nEnter choice: ";
//         int choice;
//         cin >> choice;
//         cin.ignore();

//         if (choice == 1)
//             bookDB.displayAll();
//         else if (choice == 2)
//         {
//             cout << "Enter search keyword: ";
//             string keyword;
//             getline(cin, keyword);
//             vector<Book *> results = bookDB.search(keyword);
//             if (results.empty())
//                 cout << "No books found!\n";
//             else
//                 for (auto book : results)
//                     book->display();
//         }
//         else if (choice == 3)
//         {
//             cout << "Enter Book ISBN to borrow: ";
//             string isbn;
//             getline(cin, isbn);
//             vector<Book *> books = bookDB.search(isbn);
//             if (!books.empty())
//                 user->borrowBook(books[0]);
//             else
//                 cout << "Book not found!\n";
//         }
//         else if (choice == 4)
//         {
//             cout << "Enter Book ISBN to return: ";
//             string isbn;
//             getline(cin, isbn);
//             vector<Book *> books = bookDB.search(isbn);
//             if (!books.empty())
//                 user->returnBook(books[0]);
//             else
//                 cout << "Book not found!\n";
//         }
//         else if (choice == 5)
//             cout << "Fine amount: Rs." << user->getFine() << "\n";
//         else if (choice == 6)
//             user->settleFine();
//         else if (choice == 7)
//             break;
//         else
//             cout << "Invalid choice!\n";
//     }
// }

// void librarianMenu(Librarian *librarian, BookDB &bookDB, UserDB &userDB)
// {
//     while (true)
//     {
//         cout << "\n1. Add book\n2. Remove book\n3. Update book\n4. Add user\n5. Remove user\n6. Logout\nEnter choice: ";
//         int choice;
//         cin >> choice;
//         cin.ignore();

//         if (choice == 1)
//         {
//             string isbn, title, author, publisher;
//             int year;
//             char status = 'a';
//             cout << "Enter ISBN: ";
//             getline(cin, isbn);
//             cout << "Enter Title: ";
//             getline(cin, title);
//             cout << "Enter Author: ";
//             getline(cin, author);
//             cout << "Enter Publisher: ";
//             getline(cin, publisher);
//             cout << "Enter Year: ";
//             cin >> year;
//             cin.ignore();
//             bookDB.add(Book(isbn, title, author, publisher, year, status));
//         }
//         else if (choice == 2)
//         {
//             cout << "Enter Book ISBN to remove: ";
//             string isbn;
//             getline(cin, isbn);
//             bookDB.remove(isbn);
//         }
//         else if (choice == 3)
//         {
//             cout << "Enter Book ISBN to update: ";
//             string isbn;
//             getline(cin, isbn);

//             vector<Book *> books = bookDB.search(isbn);
//             if (books.empty())
//             {
//                 cout << "Book not found!\n";
//                 return;
//             }

//             Book *book = books[0];
//             char status = book->getStatus();

//             string title, author, publisher;
//             int year;
//             cout << "Enter new Title: ";
//             getline(cin, title);
//             cout << "Enter new Author: ";
//             getline(cin, author);
//             cout << "Enter new Publisher: ";
//             getline(cin, publisher);
//             cout << "Enter new Year: ";
//             cin >> year;
//             cin.ignore();

//             Book updatedBook(title, author, isbn, publisher, year, status);
//             bookDB.update(updatedBook, isbn);

//             cout << "Book updated successfully!\n";
//         }
//         else if (choice == 4)
//         {
//             string id, name, password;
//             char role;

//             cout << "Enter User ID: ";
//             getline(cin, id);
//             cout << "Enter Name: ";
//             getline(cin, name);
//             cout << "Enter Password: ";
//             getline(cin, password);
//             cout << "Enter Role (s: Student, f: Faculty, l: Librarian): ";
//             cin >> role;
//             cin.ignore();

//             User *newUser = nullptr;
//             if (role == 's')
//                 newUser = new Student(name, id, password);
//             else if (role == 'f')
//                 newUser = new Faculty(name, id, password);
//             else if (role == 'l')
//                 newUser = new Librarian(name, id, password);
//             else
//             {
//                 cout << "Invalid role!\n";
//                 return;
//             }

//             userDB.add(newUser);
//             cout << "User added successfully!\n";
//         }
//         else if (choice == 5)
//         {
//             cout << "Enter User ID to remove: ";
//             string id;
//             getline(cin, id);
//             userDB.remove(id);
//         }
//         else if (choice == 6)
//             break;
//         else
//             cout << "Invalid choice!\n";
//     }
// }

// int main()
// {
//     BookDB bookDB;
//     bookDB.loadFile();

//     UserDB userDB(bookDB);
//     userDB.loadFile(bookDB);

//     while (true)
//     {
//         cout << "\nEnter User ID(or type \"exit\" to exit): ";
//         string userId;
//         getline(cin, userId);
//         if (userId == "exit")
//             break;
//         cout << "Enter Password: ";
//         string password;
//         getline(cin, password);

//         User *user = userDB.authenticate(userId, password);
//         if (!user)
//         {
//             cout << "Invalid credentials! Try again.\n";
//             continue;
//         }

//         if (dynamic_cast<Student *>(user) || dynamic_cast<Faculty *>(user))
//             studentFacultyMenu(user, bookDB);
//         else if (Librarian *librarian = dynamic_cast<Librarian *>(user))
//             librarianMenu(librarian, bookDB, userDB);
//     }

//     return 0;
// }
#include "book_db.hpp"
#include "user_db.hpp"
#include "models/student.hpp"
#include "models/faculty.hpp"
#include "models/librarian.hpp"
#include <iostream>

using namespace std;

void studentMenu(Student *student, BookDB &bookDB)
{
    while (true)
    {
        cout << "\n1. View all books\n2. Search for a book\n3. Borrow a book\n4. Return a book\n5. Check overdues (if any)\n6. Get Fine Amount\n7. Settle Fine\n8. Logout\nEnter choice: ";
        string choice_str;
        cin >> choice_str;
        int choice;
        try
        {
            choice = stoi(choice_str); // Convert input to integer
        }
        catch (const std::invalid_argument &)
        {
            cerr << "Invalid input! Please enter a valid number.\n";
            continue; // Restart the loop
        }
        catch (const std::out_of_range &)
        {
            cerr << "Number out of range! Enter a smaller value.\n";
            continue; // Restart the loop
        }
        cin.ignore();

        if (choice == 1){
            cout << "\nAll Books:\n";
            cout << "ISBN | Title | Author | Publisher | Year | Status(b=borrowed,a=available,r=reserved)\n";
            bookDB.displayAll();
        }
        else if (choice == 2)
        {
            cout << "Enter search keyword: ";
            string keyword;
            getline(cin, keyword);
            vector<Book *> results = bookDB.search(keyword);
            if (results.empty())
                cout << "No books found!\n";
            else
                for (auto book : results)
                    book->display();
        }
        else if (choice == 3)
        {
            cout << "Enter Book ISBN to borrow: ";
            string isbn;
            getline(cin, isbn);
            vector<Book *> books = bookDB.search(isbn);
            if (!books.empty())
                student->borrowBook(books[0]);
            else
                cout << "Book not found!\n";
        }
        else if (choice == 4)
        {
            cout << "Enter Book ISBN to return: ";
            string isbn;
            getline(cin, isbn);
            vector<Book *> books = bookDB.search(isbn);
            if (!books.empty())
                student->returnBook(books[0]);
            else
                cout << "Book not found!\n";
        }
        else if (choice == 5)
        {
            bool overdue = false;
            vector<pair<Book *, time_t> > issuedBooks = student->getIssuedBooks();
            for (auto &entry : issuedBooks)
            {
                int daysLate = difftime(time(0), entry.second) / (60); // using minutes as asked
                if (daysLate > 15)
                {
                    cout << "You have the book (with isbn:" << entry.first->getIsbn() << ") which is issued for "<< daysLate <<" (more than 15 days is considere overdue). Return it first to borrow more books!" << endl;
                    overdue = true;
                }
            }
            if (!overdue)
                cout << "No overdue books!\n";
        }
        else if (choice == 6)
        {
            cout << "Fine will be added only if you have any late returns\n";
            cout << "Fine amount: Rs." << student->getFine() << "\n";
        }

        else if (choice == 7)
            student->settleFine();
        else if (choice == 8)
            break;
        else
            cout << "Invalid choice!\n";
    }
}

void facultyMenu(Faculty *faculty, BookDB &bookDB)
{
    while (true)
    {
        cout << "\n1. View all books\n2. Search for a book\n3. Borrow a book\n4. Return a book\n5. Check overdue (if any)\n6. Logout\nEnter choice: ";
        string choice_str;
        cin >> choice_str;
        int choice;
        try
        {
            choice = stoi(choice_str); // Convert input to integer
        }
        catch (const std::invalid_argument &)
        {
            cerr << "Invalid input! Please enter a valid number.\n";
            continue; // Restart the loop
        }
        catch (const std::out_of_range &)
        {
            cerr << "Number out of range! Enter a smaller value.\n";
            continue; // Restart the loop
        }
        cin.ignore();

        if (choice == 1){
            cout << "\nAll Books:\n";
            cout << "ISBN | Title | Author | Publisher | Year | Status(b=borrowed,a=available,r=reserved)\n";
            bookDB.displayAll();
        }
        else if (choice == 2)
        {
            cout << "Enter search keyword: ";
            string keyword;
            getline(cin, keyword);
            vector<Book *> results = bookDB.search(keyword);
            if (results.empty())
                cout << "No books found!\n";
            else
                for (auto book : results)
                    book->display();
        }
        else if (choice == 3)
        {
            cout << "Enter Book ISBN to borrow: ";
            string isbn;
            getline(cin, isbn);
            vector<Book *> books = bookDB.search(isbn);
            if (!books.empty())
                faculty->borrowBook(books[0]);
            else
                cout << "Book not found!\n";
        }
        else if (choice == 4)
        {
            cout << "Enter Book ISBN to return: ";
            string isbn;
            getline(cin, isbn);
            vector<Book *> books = bookDB.search(isbn);
            if (!books.empty())
                faculty->returnBook(books[0]);
            else
                cout << "Book not found!\n";
        }
        else if (choice == 5)
        {
            bool overdue = false;
            vector<pair<Book *, time_t> > issuedBooks = faculty->getIssuedBooks();
            for (auto &entry : issuedBooks)
            {
                int daysLate = difftime(time(0), entry.second) / (60); // using minutes as asked
                if (daysLate > 30)
                {
                    cout << "You have the book (with isbn:" << entry.first->getIsbn() << ") which is issued for "<< daysLate <<" (more than 30 days are considered overdue). (You can still keep it till 60 days before your borrowing services are temporarily disabled)" << endl;
                    overdue = true;
                }
            }
            if (!overdue)
                cout << "No overdue books!\n";
        }
        else if (choice == 6)
            break;
        else
            cout << "Invalid choice!\n";
    }
}

void librarianMenu(Librarian *librarian, BookDB &bookDB, UserDB &userDB)
{
    while (true)
    {
        cout << "\n1. View all books\n2. View all users\n3. Add book\n4. Remove book\n5. Update book\n6. Add user\n7. Remove user\n8. Logout\nEnter choice: ";
        string choice_str;
        cin >> choice_str;
        int choice;
        try
        {
            choice = stoi(choice_str); // Convert input to integer
        }
        catch (const std::invalid_argument &)
        {
            cerr << "Invalid input! Please enter a valid number.\n";
            continue; // Restart the loop
        }
        catch (const std::out_of_range &)
        {
            cerr << "Number out of range! Enter a smaller value.\n";
            continue; // Restart the loop
        }
        cin.ignore();

        if (choice == 1)
        {
            cout << "\nAll Books:\n";
            cout << "ISBN | Title | Author | Publisher | Year | Status(b=borrowed,a=available,r=reserved)\n";
            bookDB.displayAll();
        }
        else if (choice == 2)
        {
            cout << "\nAll Users:\n";
            userDB.displayAll();
        }
        else if (choice == 3)
        {
            string isbn, title, author, publisher;
            int year;
            char status;
            cout << "Enter ISBN: ";
            getline(cin, isbn);
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            cout << "Enter Publisher: ";
            getline(cin, publisher);
            cout << "Enter Status (a: Available, r: Reserved): ";
            cin >> status;
            cout << "Enter Year: ";
            cin >> year;
            cin.ignore();
            bookDB.add(Book(title, author, isbn, publisher, year, status));
        }
        else if (choice == 4)
        {
            cout << "Enter Book ISBN to remove: ";
            string isbn;
            getline(cin, isbn);
            bookDB.remove(isbn);
        }
        else if (choice == 5)
        {
            cout << "Enter Book ISBN to update: ";
            string isbn;
            getline(cin, isbn);

            vector<Book *> books = bookDB.search(isbn);
            if (books.empty())
            {
                cout << "Book not found!\n";
                return;
            }

            Book *book = books[0];
            char status = book->getStatus();

            string title, author, publisher;
            int year;
            cout << "Enter new Title: ";
            getline(cin, title);
            cout << "Enter new Author: ";
            getline(cin, author);
            cout << "Enter new Publisher: ";
            getline(cin, publisher);
            cout << "Enter new Year: ";
            cin >> year;
            cin.ignore();

            Book updatedBook(title, author, isbn, publisher, year, status);
            bookDB.update(updatedBook, isbn);

            cout << "Book updated successfully!\n";
        }
        else if (choice == 6)
        {
            string id, name, password;
            char role;

            cout << "Enter User ID: ";
            getline(cin, id);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Password: ";
            getline(cin, password);
            cout << "Enter Role (s: Student, f: Faculty, l: Librarian): ";
            cin >> role;
            cin.ignore();

            User *newUser = nullptr;
            if (role == 's')
                newUser = new Student(name, id, password);
            else if (role == 'f')
                newUser = new Faculty(name, id, password);
            else if (role == 'l')
                newUser = new Librarian(name, id, password);
            else
            {
                cout << "Invalid role!\n";
                return;
            }

            userDB.add(newUser);
            cout << "User added successfully!\n";
        }
        else if (choice == 7)
        {
            cout << "Enter User ID to remove: ";
            string id;
            getline(cin, id);
            userDB.remove(id);
        }
        else if (choice == 8)
            break;
        else
            cout << "Invalid choice!\n";
    }
}

int main()
{
    BookDB bookDB;
    bookDB.loadFile();

    UserDB userDB(bookDB);
    userDB.loadFile(bookDB);

    while (true)
    {
        cout << "\nEnter User ID(or type \"exit\" to exit): ";
        string userId;
        getline(cin, userId);
        if (userId == "exit")
            break;
        cout << "Enter Password: ";
        string password;
        getline(cin, password);

        User *user = userDB.authenticate(userId, password);
        if (!user)
        {
            cout << "Invalid credentials! Try again.\n";
            continue;
        }

        if (Student *student = dynamic_cast<Student *>(user))
            studentMenu(student, bookDB);
        else if (Faculty *faculty = dynamic_cast<Faculty *>(user))
            facultyMenu(faculty, bookDB);
        else if (Librarian *librarian = dynamic_cast<Librarian *>(user))
            librarianMenu(librarian, bookDB, userDB);
    }

    return 0;
}
