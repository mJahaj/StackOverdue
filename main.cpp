
#include "Book.h"
#include <fstream>
#include <iostream>
#include <map>
#include <iterator>
#include "LibraryBooks.h"
#include "Account.h"
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

  ifstream inpAcc;
  inpAcc.open(bookFile);
  if(inpAcc.fail()){
  	cout << "fail to open"<< endl;
  }else{
  	cout << "Opened success"<< endl;
  }

  string strCons;
  getline(inpAcc, strCons);
  
  Account acc;
  inpAcc >> acc;
  acc.printAccountShort();
  Book tb("Cool Book", "TripleDoor", "Mystery", 1);
  acc.takeBook(&tb);


  LibraryBooks library;
  library.addBook();
  library.addBook();
  //acc.printAccountShort();
  //Book testB;
  //inpBooks >> testB;
  //testB.setBorrowerId(2);
//testB.setBorrowerId(5);
//testB.setBorrowerId(2);
//testB.setBorrowerId(1);
//testB.setBorrowerId(2);
//testB.setBorrowerId(2);
//testB.setBorrowerId(2);

  
  /*
  Book testB2;
  inpBooks >> testB2;
  
  Book testB3;
  inpBooks >> testB3;
  

  map <int, Book*> lib;
  lib.insert(std::pair<int, Book*>(testB.getId(), &testB));
  lib.insert(std::pair<int, Book*>(testB2.getId(), &testB2));
  lib.emplace(testB3.getId(), &testB3);

  auto it =  lib.end();
  --it;
  int newId = it->first;
  newId++;
  cout << newId << endl;
  */

  //for(auto it = lib.begin(); it != lib.end(); ++it){
    //it->second->printShortDescription();
  //}
  //cout  << "_-----------------_"<< endl;
  
  //LibraryBooks library;
  //inpBooks >> library;
  
  //library.searchByAuthorPhrase("Cec");
  return 0;	
}