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

class StackOverdue{
public:
  StackOverdue(string libraryFile, string accountsFile);
  //this function loads the books and accounts from the files
  void setStackOverdue(string libraryFile, string accountFile);
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
  void timeWarp();
  //Export the accounts data to files
  void exportAccounts(string accountsFile);
  void systemDiagnostics();
  void removeAccount();
private:
  LibraryBooks library;
  unsigned int time;
  int accountCount;
  int largestAccountId;

  void readAccountsInputStream(ifstream& accountsInputFileHandle);
  bool isValidInt(string str);
  map<int, Account*> theAccounts;
  //maybe set to keep track of all id's used for generating new id
};

#endif