#include "user.hpp"
#include <string>
#include <iostream>
using namespace std;

User::User(string name, string id, string password, char role)
{
    this->name = name;
    this->id = id;
    this->password = password;
    this->role = role;
}

User::User(string name, string password, char role)
{
    this->name = name;
    this->id = to_string(time(0)) + to_string(rand() % 100);
    this->password = password;
    this->role = role;
}

User::~User() {}

void User::setName(string name)
{
    this->name = name;
}

void User::setId(string id)
{
    this->id = id;
}

void User::setPassword(string password)
{
    this->password = password;
}

void User::setRole(char role)
{
    this->role = role;
}

string User::getName()
{
    return name;
}

string User::getId()
{
    return id;
}

string User::getPassword()
{
    return password;
}

char User::getRole()
{
    return role;
}


