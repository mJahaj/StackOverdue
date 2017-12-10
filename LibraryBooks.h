#ifndef LIBRARYBOOKS_H
#define LIBRARYBOOKS_H

#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include "Book.h"
#include <sstream>
#include "Account.h"
#include <vector>
using namespace std;
//Represents all of the books in the system
class LibraryBooks{
public:
  LibraryBooks();
  ~LibraryBooks();
  void printAllById();        //TIME: O(n)
  void printAllByTitle();     //TIME: O(n)
  void printAllByAuthor();    //TIME: O(n)
  void printAllByGenre();     //TIME: O(n)
  void printAllByPopularity();//TIME: O(n)
  void printSpecificBook();   //TIME: O(log n)
  void searchByPhrase();      
  void searchByTitlePhrase(string phrase);//TIME O(n^2)
  void searchByAuthorPhrase(string phrase);//TIME: O(n^2)
  void addBook();//TIME: O(log n)

  //Give a specified book to an account without checking if the
  //account has 10 books or overdue books. Used for when an account
  //is first set up.
  bool giveBookUnconditional(int bookID, Book*& tempBook);//TIME: O(log n)
  //Give a book to an account if the book exists and if the account
  //does not have a block
  void giveBookConditional(Account* givetoThisAcc, int bookId, int currTime); 
  void setBooksCurrDate(int date);
  int librarySize(){return books.size();}
  void exportBooks(string expFile);
  int numOfBooksOverdue();//  TIME: O(n)
  void removeBook();
  void returnBook(int currDate);
  void browse();
  void giveBookRecommendation(vector<string>& genres, string favoriteAuthor, int accId);
  friend istream& operator>>(istream& bookFile, LibraryBooks& bookS);

  
private:
  int bookCount;
  int largestBookId;
  map<int, Book*> books; 

  bool foundPhrase(string phrase, string str);
  bool bookAlreadyExists(string, string);
  bool isValidInt(string str);
  int generateId();//not used
};

#endif