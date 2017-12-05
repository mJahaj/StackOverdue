
#include "StackOverdue.h"

StackOverdue::StackOverdue(string libraryFile, string accountsFile){
  time = 1;
  setStackOverdue(libraryFile, accountsFile);
  library.setBooksCurrDate(time);
  commandLoop();

}

void StackOverdue::setStackOverdue(string libraryFile, string accountFile){
  
  if(libraryFile == ""){
  	cout << "No books provided."<< endl;
  }else{
  	ifstream libraryInputFileHandle;
  	libraryInputFileHandle.open(libraryFile);
  	if(libraryInputFileHandle.fail()){
  	  cout << "Could not find file \"" << libraryFile << "\". Skipping." << endl;
  	}else{
  	  cout << "Loading books from \"" << libraryFile << "\"." << endl;
  	  libraryInputFileHandle >> library;
  	}
  }

  if(accountFile == ""){
  	cout << "No accounts provided."<< endl;
  }else{
  	ifstream accountsInputFileHandle;
  	accountsInputFileHandle.open(accountFile);
  	if(accountsInputFileHandle.fail()){
  	  cout << "Could not find file \"" << accountFile << "\". Skipping." << endl;
  	}else{
  	  cout << "Loading accounts from \"" << accountFile << "\"." << endl;
  	  readAccountsInputStream(accountsInputFileHandle);
  	}
  }
}

void StackOverdue::printHelp(){
  cout << "BROWSE: Provides the status of all the books." << endl;
  cout << "BOOK: Provides the status of a specific book." << endl;
  cout << "SEARCH: Searches for all books with a key-phrase in the title or author." << endl;
  cout << "ACCOUNTS: Provides account snapshots for all user accounts." << endl;
  cout << "ACCOUNT: Provides an account snapshot for a specific user account." << endl;
  cout << "CHECKOUT: Checks a book out to a user account." << endl;
  cout << "RENEW: Renews a checked out book. (Up to two times allowed)" << endl;
  cout << "RETURN: Returns a checked out book." << endl;
  cout << "RECOMMEND: Generates a list of recommended books for a given user." << endl;
  cout << "ADDB: Adds a new book to the library." << endl;
  cout << "REMOVEB: Removes a specific book from the library." << endl;
  cout << "ADDA: Creates a new user account in the library." << endl;
  cout << "REMOVEA: Removes a specific user account from the library." << endl;
  cout << "SYSTEM: Provides diagnostic information about the system." << endl;
  cout << "TIME: Fast forwards the system time by a specified number of days." << endl;
  cout << "EXPORT: Exports the library’s books and accounts to files." << endl;
  cout << "HELP: Displays this help menu." << endl;
  cout << "EXIT: Exits the program." << endl;
}

void StackOverdue::commandLoop(){
  string userInput = "";

  while(userInput != "EXIT"){
  	cout << "> ";
  	getline(cin, userInput);
    
    if(userInput == "BROWSE"){
      library.browse();
      cout << endl;
    }else if(userInput == "HELP"){
      printHelp();
      cout << endl;
    }else if(userInput == "BOOK"){
      if(library.librarySize() <= 0){
      	cout << "No books in your library.\n" << endl;
      }else{
      	library.printSpecificBook();
        cout << endl;
      }
    }else if(userInput == "SEARCH"){
      if(library.librarySize() <= 0){
      	cout << "No books in your library.\n" << endl;
      }else{
        library.searchByPhrase();
        cout << endl;
      }
    }

    //else{
      //cout << "Invalid command.\n" << endl;
    //}

  }

  cout << "Thank you for using StackOverdue!" << endl;
}

//------------------Helper Functions-----------------------

void StackOverdue::readAccountsInputStream(ifstream& accountsInputFileHandle){
  accountsInputFileHandle >> accountCount;
  string consumeEmpty;
  getline(accountsInputFileHandle, consumeEmpty);
  char delim = '|';
  for(int i = 0; i < accountCount; i++){
  	string accData = "";
    string tokenAcc;
    vector<string> accTokens;
    getline(accountsInputFileHandle, accData);
    stringstream ss(accData);//split string
    while(getline(ss, tokenAcc, delim)){
  	  accTokens.push_back(tokenAcc);
    }
    
    Account* newAcc = new Account(accTokens[1], stoi(accTokens[0]));//create account
    
    for(int i = 0; i < stoi(accTokens[2]); i++){
      string booksData = "";
      string tokenBooks;
      vector<string> bookTokens;
      getline(accountsInputFileHandle, booksData);
      stringstream ss(booksData);//split string
      while(getline(ss, tokenBooks, delim)){
  	    bookTokens.push_back(tokenBooks);
      }
      
      Book* tempBookPtr;
      if(!library.giveBookUnconditional(stoi(bookTokens[0]), tempBookPtr)){
      	cout << "Could not find library book with ID# " << bookTokens[0] << "." << endl;
      }else{
      	tempBookPtr->setDueDate(stoi(bookTokens[1]));
      	tempBookPtr->setTimesRenewed(stoi(bookTokens[2]));
      	tempBookPtr->setBorrowerId(newAcc->getAccountId());
      	newAcc->takeBook(tempBookPtr);
      }
      
    } 
    //newAcc->printAccountShort();
    theAccounts.emplace(newAcc->getAccountId(), newAcc);
    //auto it = theAccounts.end();
    //--it;
    //it->second->printAccountShort();
    
  }//for1
  
}

