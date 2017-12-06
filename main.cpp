
//#include "Book.h"
#include <fstream>
#include <iostream>
#include <map>
#include <iterator>
//#include "LibraryBooks.h"
//#include "Account.h"
#include "StackOverdue.h"
using namespace std;

int main(int argc, char **argv){
  string bookFile = "";
  string accountFile = "";
  if (argc == 2) {
    bookFile = argv[1];
  } else if (argc >= 3) {
    bookFile = argv[1];
    accountFile = argv[2];
  }

  StackOverdue newStackOverdue(bookFile, accountFile);

  return 0;	
}