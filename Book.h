#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <sstream>
#include <set>
#include <string>
#include <vector>
using namespace std;

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
  //return true if the book is overude
  bool isOverdue(){return overdue;}
  //store the ID of the current account that has this book
  void setBorrowerId(int accountId);
  //sets the due date of the book
  void setDueDate(int date){dueDate = date;}
  //set the current system date
  void setCurrDate(int date);
  //find out if the book is overdue
  void findIfOverdue();
  //set the amount of times this book has been renewed
  void setTimesRenewed(int count){timesRenewed = count;}
  //print full description of the book
  void printFullDescription();
  //print full description of the book without id
  void printFullDescriptionNoId();
  //print short description of the book
  void printShortDescription();//--------
  void printShortDescription2();  
  void resetAfterReturn();
  //returns true if the accoundId had previously read this book
  bool userReadThis(int accId);
  friend istream& operator>>(istream& input, Book& book);
private:
  int id;
  string author;
  string title;
  string genre;
  int popularity;
  int currDate;
  int dueDate;
  int timesRenewed;

  int borrowerId;
  bool borrowed;
  bool overdue;
  

  set<int> usersReadThis;
};

#endif