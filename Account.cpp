
#include "Account.h"

void Account::printAccountShort(){
  cout << name << " (AccountID# " << id << "). ";
  if(accountBooks.size() <= 0){
  	cout << "No books checked out." << endl;
  }else{
  	cout << accountBooks.size() << " books checked out:" << endl;
  	int i = 1;
  	for(auto it = accountBooks.begin(); it != accountBooks.end(); ++it, ++i){
  	  cout << "\t" << i << ". "; 
  	  it->second->printShortDescription2();
    }
  }
}

void Account::printAccountFull(){
  cout << "Name: " <<name << endl;
  cout << "AccountID#: " << id << endl;
  if(accountBooks.size() <= 0){
  	cout << "No books checked out." << endl;
  }else{
  	int overdueCount = numOfBooksOverdue();
  	if(overdueCount <= 0){
  	  cout << accountBooks.size() << " books checked out:" << endl;
  	}else{
  	  cout << accountBooks.size() << " books checked out: (" << overdueCount <<" overdue):"<<endl;
  	}
  	int i = 1;
  	for(auto it = accountBooks.begin(); it != accountBooks.end(); ++it, i++){
  	  cout << "\t" << i << "." <<endl;
  	  it->second->printFullDescriptionNoId();
  	}
  }
}

Account::Account(string namE, int iD){
  name = namE;
  id = iD;
}

Account::Account(){
  name = "";
  id = -1;
}

int Account::numOfBooksOverdue(){
  int overdueCount = 0;
  for(auto it = accountBooks.begin(); it != accountBooks.end(); ++it){
  	if(it->second->isOverdue()){
  	  overdueCount++;
  	}
  }
  return overdueCount;
}

void Account::takeBook(Book* book){
  auto itGenre = genresRead.find(book->getGenre());
  if(itGenre == genresRead.end()){//if genre never was read
  	genresRead.insert(std::pair<string, int> (book->getGenre(), 1));
  }else{
  	if(!book->userReadThis(id)){//if user never read the book
  	  itGenre->second++;
  	}
  }

  auto itAuthor = authorsRead.find(book->getAuthor());
  if(itAuthor == authorsRead.end()){//if user previously did not read from this author
  	authorsRead.insert(std::pair<string, int> (book->getAuthor(), 1));
  }else{
  	itAuthor->second++;
  }

  accountBooks.insert(std::pair<int, Book*> (book->getId(), book));
}

void Account::forceReturnAll(){
  for(auto it = accountBooks.begin(); it != accountBooks.end(); ++it){
  	it->second->resetAfterReturn();
  	cout <<"\""<< it->second->getTitle() << "\"" << " by " << it->second->getAuthor()
  	<< " (BookID# " << it->second->getId() << ") force returned." << endl;
  }
}

void Account::returnSpecifiedBook(int bookId){
  auto it = accountBooks.find(bookId);
  it->second->resetAfterReturn();
  accountBooks.erase(it);
}

istream& operator>>(istream& input, Account& acc){

  string accountData = "";
  string token;
  char delim = '|';
  vector<string> tokens;
  //split the string into tokens
  getline(input, accountData);
  stringstream ss(accountData);
  while(getline(ss, token, delim)){
  	tokens.push_back(token);
  }  
  
  stringstream strToIntId(tokens[0]);
  strToIntId >> acc.id;
  acc.name = tokens[1];

  int booksHad;
  stringstream strToIntBooks(tokens[0]);
  strToIntBooks >> booksHad;
  return input;
}

ostream& operator<<(ostream& os, Account& acc){
  os << acc.id << "|" << acc.name << "|" << acc.accountBooks.size() << endl;

  for(auto it = acc.accountBooks.begin(); it != acc.accountBooks.end(); ++it){
  	os << it->second->getId() << "|" << it->second->getDueDate() << "|" 
  	<< it->second->getTimesRenewed() << endl;
  }
  return os;
}