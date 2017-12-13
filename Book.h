#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <sstream>
#include <set>
#include <unordered_set>
#include <string>
#include <vector>
using namespace std;

class Account;
//Represents a single Book
class Book{
public:
  Book();
  Book(string, string, string, int);
  ~Book(){}
  int getId(){return id;}
  string getAuthor(){return author;}
  string getTitle(){return title;}
  string getGenre(){return genre;}
  int getPopularity(){return popularity;}
  int getDueDate(){return dueDate;}
  int getTimesRenewed(){return timesRenewed;}
  //return true if the book is checked out
  bool getBorrowed(){return borrowed;}
  bool isOverdue(){return overdue;}
  //returns the account pointer of the current book borrower
  Account* getCurrAccountBorrower(){return currBorrowerAccount;}
  //store the ID of the current account that has this book
  void setBorrowerId(int accountId, Account* whoBorrowed);
  void setDueDate(int date){dueDate = date;}
  //set the current system date in the book
  void setCurrDate(int date);
  void findIfOverdue();
  void setTimesRenewed(int count){timesRenewed = count;}
  void printFullDescription();
  void printFullDescriptionNoId();
  void printShortDescription();
  void printShortDescription2(); //(Availability not included)
  void resetAfterReturn();
  //returns true if a specified account had checked out this book
  bool userReadThis(int accId);//TIME: O(log n)
  friend istream& operator>>(istream& input, Book& book);
private:
  int id;
  string author;
  string title;
  string genre;
  int popularity;
  int currDate;//current system date
  int dueDate;
  int timesRenewed;

  int borrowerId;
  bool borrowed;
  bool overdue;
  Account* currBorrowerAccount;

  unordered_set<int> usersReadThis;
};

#endif