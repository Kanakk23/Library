// #include "user_db.hpp"
// #include "models/student.hpp"
// #include "models/faculty.hpp"
// #include <iostream>
// #include <fstream>
// #include <sstream>

// using namespace std;

// UserDB::UserDB(BookDB &bookDB)
// {
//     filename = "users_data.txt";
//     loadFile(bookDB); // Load users along with their issued books from BookDB
// }

// UserDB::~UserDB()
// {
//     saveFile();

//     // Free allocated memory
//     for (auto user : users)
//     {
//         delete user;
//     }
// }

// // Add a user
// void UserDB::add(User *user)
// {
//     users.push_back(user);
// }

// // Remove a user by ID
// void UserDB::remove(string ID)
// {
//     for (auto it = users.begin(); it != users.end(); ++it)
//     {
//         if ((*it)->getId() == ID)
//         {
//             delete *it; // Free memory before erasing
//             users.erase(it);
//             break;
//         }
//     }
// }

// // Update user details
// void UserDB::update(User *user, string ID)
// {
//     for (auto &existingUser : users)
//     {
//         if (existingUser->getId() == ID)
//         {
//             *existingUser = *user;
//         }
//     }
// }

// // Display all users
// void UserDB::displayAll()
// {
//     for (size_t i = 0; i < users.size(); i++)
//     {
//         cout << "User " << i + 1 << ":\n";
//         users[i]->display();
//         cout << endl;
//     }
// }

// // Search for users by keyword (ID, name, role)
// vector<User *> UserDB::search(string keyword)
// {
//     vector<User *> result;

//     for (auto &user : users)
//     {
//         if (user->getId() == keyword ||
//             user->getName().find(keyword) != string::npos ||
//             user->getRole() == keyword[0])
//         {
//             result.push_back(user);
//         }
//     }

//     return result;

// } // Save users to a file, including issued books and book history
// void UserDB::saveFile()
// {
//     ofstream file(filename);
//     if (!file)
//     {
//         cerr << "Error: Unable to open file for writing!\n";
//         return;
//     }

//     for (const auto &user : users)
//     {
//         file << user->getId() << "|"
//              << user->getName() << "|"
//              << user->getPassword() << "|"
//              << user->getRole() << "|";

//         // Save issued books
//         vector<Book *> issuedBooks = user->getIssuedBooks();
//         if (!issuedBooks.empty())
//         {
//             for (size_t i = 0; i < issuedBooks.size(); i++)
//             {
//                 file << issuedBooks[i]->getIsbn();
//                 if (i < issuedBooks.size() - 1)
//                     file << ",";
//             }
//         }
//         file << "|"; // Separator

//         // Save book history
//         vector<string> bookHistory = user->getBookHistory();
//         if (!bookHistory.empty())
//         {
//             for (size_t i = 0; i < bookHistory.size(); i++)
//             {
//                 file << bookHistory[i];
//                 if (i < bookHistory.size() - 1)
//                     file << ",";
//             }
//         }
//         file << "\n"; // End of user entry
//     }

//     file.close();
// }

// void UserDB::loadFile(BookDB &bookDB)
// {
//     ifstream file(filename);
//     if (!file)
//     {
//         cerr << "Warning: No existing user data found. Creating new database.\n";
//         return;
//     }

//     string id, name, password, issuedBooksStr, bookHistoryStr;
//     char role;

//     while (getline(file, id, '|') &&
//            getline(file, name, '|') &&
//            getline(file, password, '|') &&
//            (file >> role) &&
//            file.ignore(1, '|') &&
//            getline(file, issuedBooksStr, '|') &&
//            getline(file, bookHistoryStr))
//     {
//         User *user = nullptr;

//         if (role == 's')
//             user = new Student(name, id, password);
//         else if (role == 'f')
//             user = new Faculty(name, id, password);
//         else
//         {
//             cerr << "Invalid role in user data file: " << role << endl;
//             continue;
//         }

//         // ✅ Fix: Use loadingBook() instead of borrowBook()
//         if (!issuedBooksStr.empty())
//         {
//             stringstream ss(issuedBooksStr);
//             string isbn;
//             while (getline(ss, isbn, ','))
//             {
//                 vector<Book *> foundBooks = bookDB.search(isbn); // Get pointers

//                 if (!foundBooks.empty())
//                 {
//                     Student *student = dynamic_cast<Student *>(user);
//                     Faculty *faculty = dynamic_cast<Faculty *>(user);
//                     if (student)
//                         student->loadingBook(foundBooks[0]); // Directly load book
//                     else if (faculty)
//                         faculty->loadingBook(foundBooks[0]); // Directly load book
//                 }
//                 else
//                 {
//                     cerr << "Warning: Book with ISBN " << isbn << " not found in BookDB.\n";
//                 }
//             }
//         }

//         // ✅ Fix: Load book history properly
//         if (!bookHistoryStr.empty())
//         {
//             stringstream ss(bookHistoryStr);
//             string isbn;
//             while (getline(ss, isbn, ','))
//             {
//                 user->addHistoryBook(isbn);
//             }
//         }

//         users.push_back(user);
//     }

//     file.close();
// }

// User *UserDB::authenticate(const std::string &userId, const std::string &password)
// {
//     for (User *user : users)
//     {
//         if (user->getId() == userId && user->getPassword() == password)
//         {
//             return user; // Authentication successful
//         }
//     }
//     return nullptr; // Authentication failed
// }

#include "user_db.hpp"
#include "models/student.hpp"
#include "models/faculty.hpp"
#include "models/librarian.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

UserDB::UserDB(BookDB &bookDB)
{
    filename = "users_data.txt";
    loadFile(bookDB); // Load users along with their issued books from BookDB
}

UserDB::~UserDB()
{
    saveFile();

    // Free allocated memory
    for (auto user : users)
    {
        delete user;
    }
}

// Add a user
void UserDB::add(User *user)
{
    users.push_back(user);
}

// Remove a user by ID
void UserDB::remove(string ID)
{
    for (auto it = users.begin(); it != users.end(); ++it)
    {
        if ((*it)->getId() == ID)
        {
            delete *it; // Free memory before erasing
            users.erase(it);
            break;
        }
    }
}

// Update user details
void UserDB::update(User *user, string ID)
{
    for (auto &existingUser : users)
    {
        if (existingUser->getId() == ID)
        {
            *existingUser = *user;
        }
    }
}

// Display all users
void UserDB::displayAll()
{
    for (size_t i = 0; i < users.size(); i++)
    {
        cout << "User " << i + 1 << ":\n";
        users[i]->display();
        cout << endl;
    }
}

// Search for users by keyword (ID, name, role)
vector<User *> UserDB::search(string keyword)
{
    vector<User *> result;

    for (auto &user : users)
    {
        if (user->getId() == keyword ||
            user->getName().find(keyword) != string::npos ||
            user->getRole() == keyword[0])
        {
            result.push_back(user);
        }
    }

    return result;
}

// Save users to a file, including issued books with timestamps and book history
void UserDB::saveFile()
{
    ofstream file(filename, ios::trunc);

    if (!file)
    {
        cerr << "Error: Unable to open file for writing!\n";
        return;
    }

    for (const auto &user : users)
    {
        file << user->getId() << "|"
             << user->getName() << "|"
             << user->getPassword() << "|"
             << user->getRole() << "|"
             << user->getFine() << "|"; // Save fine amount

        // Save issued books with timestamps
        vector<pair<Book *, time_t> > borrowedBooks = user->getIssuedBooks();
        if (!borrowedBooks.empty())
        {
            for (size_t i = 0; i < borrowedBooks.size(); i++)
            {
                file << borrowedBooks[i].first->getIsbn() << ":" << borrowedBooks[i].second;
                if (i < borrowedBooks.size() - 1)
                    file << ",";
            }
        }
        file << "|"; // Separator

        // Save book history
        vector<string> bookHistory = user->getBookHistory();
        if (!bookHistory.empty())
        {
            for (size_t i = 0; i < bookHistory.size(); i++)
            {
                file << bookHistory[i];
                if (i < bookHistory.size() - 1)
                    file << ",";
            }
        }
        file << "\n"; // End of user entry
    }

    file.close();
}

// Load users from file, including issued books with timestamps and book history
void UserDB::loadFile(BookDB &bookDB)
{
    users.clear();
    ifstream file(filename);
    if (!file)
    {
        cerr << "Warning: No existing user data found. Creating new database.\n";
        return;
    }

    string id, name, password, fineStr, issuedBooksStr, bookHistoryStr;
    char role;

    while (getline(file, id, '|') &&
           getline(file, name, '|') &&
           getline(file, password, '|') &&
           (file >> role) &&
           file.ignore(1, '|') &&
           getline(file, fineStr, '|') &&
           getline(file, issuedBooksStr, '|') &&
           getline(file, bookHistoryStr))
    {
        User *user = nullptr;

        if (role == 's')
            user = new Student(name, id, password);
        else if (role == 'f')
            user = new Faculty(name, id, password);
        else if (role == 'l')
            user = new Librarian(name, id, password);
        else
        {
            cerr << "Invalid role in user data file: " << role << endl;
            continue;
        }

        // ✅ Load fine amount
        int fine = stoi(fineStr);
        user->setFine(fine);

        // ✅ Load issued books with timestamps
        if (!issuedBooksStr.empty())
        {
            stringstream ss(issuedBooksStr);
            string bookData;
            while (getline(ss, bookData, ','))
            {
                size_t pos = bookData.find(':');
                if (pos != string::npos)
                {
                    string isbn = bookData.substr(0, pos);
                    time_t borrowTime = stoll(bookData.substr(pos + 1));

                    vector<Book *> foundBooks = bookDB.search(isbn);
                    if (!foundBooks.empty())
                    {
                        Student *student = dynamic_cast<Student *>(user);
                        Faculty *faculty = dynamic_cast<Faculty *>(user);
                        if (student)
                            student->loadingBook(foundBooks[0], borrowTime); // Load book with timestamp
                        else if (faculty)
                            faculty->loadingBook(foundBooks[0], borrowTime); // Load book with timestamp
                    }
                    else
                    {
                        cerr << "Warning: Book with ISBN " << isbn << " not found in BookDB.\n";
                    }
                }
            }
        }

        // ✅ Load book history
        if (!bookHistoryStr.empty())
        {
            stringstream ss(bookHistoryStr);
            string isbn;
            while (getline(ss, isbn, ','))
            {
                user->addHistoryBook(isbn);
            }
        }

        users.push_back(user);
    }

    file.close();
}

User *UserDB::authenticate(const std::string &userId, const std::string &password)
{
    for (User *user : users)
    {
        if (user->getId() == userId && user->getPassword() == password)
        {
            return user; // Authentication successful
        }
    }
    return nullptr; // Authentication failed
}
