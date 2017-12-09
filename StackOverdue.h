#ifndef STACKOVERDUE_H
#define STACKOVERDUE_H

#include "Book.h"
#include <iostream>
#include <fstream>
#include "LibraryBooks.h"
#include <map>
#include <sstream>
#include <vector>
#include "Account.h"

using namespace std;
//Represents the Library system "StackOverdue"
class StackOverdue{
public:
  StackOverdue(string libraryFile, string accountsFile);
  //sets up the library with the provided accounts and books files
  //if the files cannot be opened, there library system will not have
  //any books or accounts from startup
  void setStackOverdue(string libraryFile, string accountFile);
  //The main UI for the user to enter commands
  void commandLoop();
  void printHelp();
  //
  void printAccountsByCheckouts();
  void printAccountsByName();
  void printAccountsById();
  void printAccounts();
  void printSpecificAccount();

  void addAccount();
  //export both library books and accounts to their respective files
  void exportBooksAccounts();
  //Move forward in time command
  void timeWarp();
  //Export the accounts data to files
  void exportAccounts(string accountsFile);
  //Displays the current Library system information
  void systemDiagnostics();
  void removeAccount();

  void checkoutBook();
  
  void renewBooks();
private:
  LibraryBooks library;
  map<int, Account*> theAccounts;
  unsigned int time;
  int accountCount;
  int largestAccountId;

  //Reads the accountsFile input stream and creates the accounts with
  //their previously checked out books 
  void readAccountsInputStream(ifstream& accountsInputFileHandle);

  bool isValidInt(string str);
  //maybe set to keep track of all id's used for generating new id
};

#endif