#pragma once
#include "models/user.hpp"
#include "models/student.hpp"
#include "models/faculty.hpp"
#include "book_db.hpp"
#include <vector>
#include <fstream>

using namespace std;

class UserDB
{
private:
    vector<User *> users;
    string filename;

public:
    UserDB(BookDB &bookDB);
    ~UserDB();
    void add(User *user);
    void remove(string id);
    void update(User *user, string id);
    void displayAll();
    vector<User *> search(string keyword);
    void saveFile();
    void loadFile(BookDB &bookDB); // Pass BookDB reference here
    User *authenticate(const string &userId, const string &password);
};
