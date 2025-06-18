#include "book.hpp"
#include <iostream>
using namespace std;

Book::Book(string title, string author, string isbn, string publisher, int year, char status)
{
	this->title = title;
	this->author = author;
	this->isbn = isbn;
	this->publisher = publisher;
	this->year = year;
	this->status = status;
}

void Book::setAuthor(string author)
{
	this->author = author;
}

void Book::setIsbn(string isbn)
{
	this->isbn = isbn;
}

void Book::setPublisher(string publisher)
{
	this->publisher = publisher;
}

void Book::setTitle(string title)
{
	this->title = title;
}

void Book::setYear(int year)
{
	this->year = year;
}

string Book::getAuthor()
{
	return author;
}

string Book::getIsbn()
{
	return isbn;
}

string Book::getPublisher()
{
	return publisher;
}

string Book::getTitle()
{
	return title;
}

int Book::getYear()
{
	return year;
}

void Book::display()
{
	cout << "Title: " << title << endl;
	cout << "Publisher: " << publisher << endl;
	cout << "Author: " << author << endl;
	cout << "ISBN: " << isbn << endl;
	cout << "Year: " << year << endl;
	cout << "Availability: " << status << endl;
}

void Book::setStatus(char status)
{
	this->status = status;
}

char Book::getStatus()
{
	return status;
}
