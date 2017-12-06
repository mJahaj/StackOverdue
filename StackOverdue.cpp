
#include "StackOverdue.h"

StackOverdue::StackOverdue(string libraryFile, string accountsFile){
  time = 1;
  largestAccountId = 0;
  setStackOverdue(libraryFile, accountsFile);
  library.setBooksCurrDate(time);
  commandLoop();

}

void StackOverdue::setStackOverdue(string libraryFile, string accountFile){
  //Read from the books input file
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
  	  libraryInputFileHandle.close();
  	}
  }
  //Read from the account input file
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
  	  accountsInputFileHandle.close();
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
    }else if(userInput == "ACCOUNTS"){
      if(theAccounts.size() <= 0){
        cout << "No accounts in your library.\n" << endl; 
      }else{
        printAccounts();
        cout << endl;
      } 
    }else if(userInput == "ACCOUNT"){
      if(theAccounts.size() <= 0){
        cout << "No accounts in your library.\n" << endl; 
      }else{
        printSpecificAccount();
        cout << endl;
      } 
    }else if(userInput == "ADDA"){
      addAccount();
      cout << endl;
    }else if(userInput == "ADDB"){
      library.addBook();
      cout << endl;
    }else if(userInput == "TIME"){
      timeWarp();
      cout << endl;
    }else if(userInput == "EXPORT"){
      cout << "Under construction" << endl;
    }

    //else{
      //cout << "Invalid command.\n" << endl;
    //}

  }

  cout << "Thank you for using StackOverdue!" << endl;
}

void StackOverdue::printAccountsByName(){
  multimap<string, Account*> sortName;

  for(auto it = theAccounts.begin(); it != theAccounts.end(); ++it){
  	sortName.insert(pair<string, Account*>(it->second->getName(), it->second));
  }
  int i = 1;
  for(auto it = sortName.begin(); it != sortName.end(); ++it, i++){
    cout << i << ". "; 
    it->second->printAccountShort();
  }
}

void StackOverdue::printAccountsById(){
  int i = 1;
  for(auto it = theAccounts.begin(); it != theAccounts.end(); ++it, i++){
  	cout << i << ". ";
  	it->second->printAccountShort();
  }
}

void StackOverdue::printAccountsByCheckouts(){
  multimap<int, Account*> sortCheckouts;

  for(auto it = theAccounts.begin(); it != theAccounts.end(); ++it){
  	sortCheckouts.insert(pair<int, Account*>(it->second->getNumOfBooks(), it->second));
  }
  int i = 1;
  for(auto it = sortCheckouts.rbegin(); it != sortCheckouts.rend(); ++it, i++){
    cout << i << ". "; 
    it->second->printAccountShort();
  }
}

void StackOverdue::printSpecificAccount(){
  string userInput;
  cout << "Enter the account id." << endl;
  cout << "> ";
  getline(cin, userInput);

  if(!isValidInt(userInput)){
    cout << "Invalid input." << endl;
  }else{
  	auto it = theAccounts.find(stoi(userInput));
  	if(it == theAccounts.end()){
  	  cout << "AccountID# " << userInput << " not found." << endl;
  	}else{
  	  it->second->printAccountFull();
  	}
  }
}

void StackOverdue::printAccounts(){
  string criteria = "";
  cout << "Enter the criteria to search by. (name/accountid/checkouts)" << endl;
  cout << "> ";
  getline(cin, criteria);

  if(criteria == "name"){
  	printAccountsByName();
  }else if(criteria == "accountid"){
  	printAccountsById();
  }else if(criteria == "checkouts"){
  	printAccountsByCheckouts();
  }else{
  	cout << "Invalid value." << endl;
  }
}

void StackOverdue::addAccount(){
  string userInput = "";
  cout << "Enter the user's name." << endl;
  cout << "> ";
  getline(cin, userInput);
  largestAccountId++;
  Account* newAccount = new Account(userInput, largestAccountId);
  theAccounts.emplace(largestAccountId, newAccount);
  accountCount++;
  cout << "AccountID# " << largestAccountId << " successfully created." << endl;
}

void StackOverdue::timeWarp(){
  cout << "Enter the number of days to time travel." << endl;
  cout << "> ";
  string userInput = "";
  getline(cin, userInput);

  if(!isValidInt(userInput)){
  	cout << "Invalid value." << endl;
  }else{
  	if(stoi(userInput) <= 0){
  	  cout << "Invalid value." << endl;
  	}else{
  	  cout << "Traveled " << stoi(userInput) << " days through time (" << time
  	  << " --> " << (time + stoi(userInput)) << ")." << endl;
  	  time = time + stoi(userInput);
  	  library.setBooksCurrDate(time);//update books current date
  	}
  }
}
//------------------Helper Functions-----------------------

void StackOverdue::readAccountsInputStream(ifstream& accountsInputFileHandle){
  accountsInputFileHandle >> accountCount;
  string consumeEmpty;
  getline(accountsInputFileHandle, consumeEmpty);
  char delim = '|';
  //populates the accounts
  for(int i = 0; i < accountCount; i++){
  	string accData = "";
    string tokenAcc;
    vector<string> accTokens;
    getline(accountsInputFileHandle, accData);
    stringstream ss(accData);//split account string into vector
    while(getline(ss, tokenAcc, delim)){
  	  accTokens.push_back(tokenAcc);
    }
                                                         //v id   
    Account* newAcc = new Account(accTokens[1], stoi(accTokens[0]));//create account
    //find largest id
    if(stoi(accTokens[0]) > largestAccountId){
      largestAccountId = stoi(accTokens[0]);
    }
    //find the books the account has checked out
    for(int i = 0; i < stoi(accTokens[2]); i++){
      string booksData = "";
      string tokenBooks;
      vector<string> bookTokens;
      getline(accountsInputFileHandle, booksData);
      stringstream ss(booksData);//split book string onto vec
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
    
    theAccounts.emplace(newAcc->getAccountId(), newAcc);
    //auto it = theAccounts.end();
    //--it;
    //it->second->printAccountShort();
    
  }//for1
  
}

bool StackOverdue::isValidInt(string str){
  unsigned int i = 0;
  if(str.length() == 1 && str[0] == '-'){
    return false;
  }
  if(str[0] == '-'){
    i = 1;
  }
  for(; i < str.length(); i++){
    if(!isdigit(str[i])){
      return false;
    }
  }
  return true;
}

