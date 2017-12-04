
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

Account::Account(string namE, int iD){
  name = namE;
  id = iD;
}

Account::Account(){
  name = "";
  id = -1;
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