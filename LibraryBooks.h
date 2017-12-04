#ifndef LIBRARYBOOKS_H
#define LIBRARYBOOKS_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include "Book.h"
#include <sstream>
using namespace std;

class LibraryBooks{
public:
  //~LibraryBooks();
  //print short description of all books by ID ascending numerical
  void printAllById();
  //print short description of all books by title ascending aphabetical
  void printAllByTitle(); 
  //print short description of all books by author ascending aphabetical
  void printAllByAuthor();
  //print short description of all books by Genre ascending aphabetical
  void printAllByGenre(); 
  //print short description of all books by popularity ascending numerical
  void printAllByPopularity();
  //print short description of books contining a given phrase in the title
  void searchByTitlePhrase(string phrase);
  //print short description of books contining a given phrase in the title
  void searchByAuthorPhrase(string phrase);
  //add a book to the current library
  void addBook();
  //give a book for setup
  bool giveBookUnconditional(int bookID, Book*& tempBook);
  friend istream& operator>>(istream& bookFile, LibraryBooks& bookS);
  
private:
  int bookCount;
  map<int, Book*> books; 

  bool foundPhrase(string phrase, string str);
  bool bookAlreadyExists(string, string);
  int generateId();
};

#endif