#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Book.h"
#include <iostream>
#include <unordered_map>
#include <map>
#include <sstream>
#include <vector>
using namespace std;
//Represents a users library account
class Account{
public:
  Account(string namE, int iD);
  Account();
  //prints a short description of te account and short description of its books
  void printAccountShort();
  int getAccountId(){return id;}
  string getName(){return name;}
  //returns the number of books in the account
  int getNumOfBooks(){return accountBooks.size();}
  void takeBook(Book* book);
  //return the number of books overdue in this account
  int numOfBooksOverdue();//TIME: O(n)
  //print a full description of the account
  void printAccountFull();
  //force return all of the books checked out
  void forceReturnAll();
  //force return a specified book
  void returnSpecifiedBook(int bookId);
  //renews all of the books with less than 2 renews 
  void renewAccountBooks();//TIME O(n)
  //Finds the two most favorite genres for the account
  void twoFavoriteGenres(vector<string>& twoGenres);
  string favoriteAuthor();
  friend istream& operator>>(istream& input, Account& acc);
  friend ostream& operator<<(ostream& os, Account& acc);  

private:
  string name;
  int id;
  unordered_map<int, Book*> accountBooks;//hold books
  unordered_map<string, int> genresRead;//hold genre history
  unordered_map<string, int> authorsRead;//hold author history
  
};

#endif
