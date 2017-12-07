#ifndef LIBRARYBOOKS_H
#define LIBRARYBOOKS_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include "Book.h"
#include <sstream>
using namespace std;

class LibraryBooks{
public:
  LibraryBooks();
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
  //finds a specific book and prints full desctiption
  void printSpecificBook();
  //
  void searchByPhrase();
  //print short description of books contining a given phrase in the title
  void searchByTitlePhrase(string phrase);
  //print short description of books contining a given phrase in the title
  void searchByAuthorPhrase(string phrase);
  //add a book to the current library
  void addBook();
  //give a book for setup
  bool giveBookUnconditional(int bookID, Book*& tempBook);
  //
  void setBooksCurrDate(int date);
  int librarySize(){return books.size();}
  //Export the books to a file
  void exportBooks(string expFile);
  //returns the number of books that are currently overdue TIME: O(n)
  int numOfBooksOverdue();
  

  void browse();
  friend istream& operator>>(istream& bookFile, LibraryBooks& bookS);

  
private:
  int bookCount;
  int largestBookId;
  map<int, Book*> books; 

  bool foundPhrase(string phrase, string str);
  bool bookAlreadyExists(string, string);
  bool isValidInt(string str);
  int generateId();
};

#endif