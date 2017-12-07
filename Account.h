#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Book.h"
#include <iostream>
#include <unordered_map>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

class Account{
public:
  Account(string namE, int iD);
  Account();
  //prints a short description of te account and short description of its books
  void printAccountShort();
  //returns the accounts id
  int getAccountId(){return id;}
  // return users name
  string getName(){return name;}
  //returns the number of books in the account
  int getNumOfBooks(){return accountBooks.size();}
  //take book and add it 
  void takeBook(Book* book);
  int numOfBooksOverdue();
  void printAccountFull();
  friend istream& operator>>(istream& input, Account& acc);
  friend ostream& operator<<(ostream& os, Account& acc);  

private:
  string name;
  int id;
  unordered_map<int, Book*> accountBooks;//hold books
  map<string, int> genresRead;//hold genre history
  map<string, int> authorsRead;
  
};

#endif