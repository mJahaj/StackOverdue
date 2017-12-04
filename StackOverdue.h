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
  void printHelp();
private:
  LibraryBooks library;
  unsigned int time;
  int accountCount;

  void readAccountsInputStream(ifstream& accountsInputFileHandle);
  map<int, Account*> theAccounts;
};

#endif