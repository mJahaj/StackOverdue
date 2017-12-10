
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
      cout << accountBooks.size() << " books checked out (" << overdueCount <<" overdue):"<<endl;
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

//Recieve a checked out book and update the favorite 
//genres and author
void Account::takeBook(Book* book){
  //update the genres the account likes
  auto itGenre = genresRead.find(book->getGenre());
  if(itGenre == genresRead.end()){//if genre never was read
    genresRead.insert(std::pair<string, int> (book->getGenre(), 1));
  }else{
    if(!book->userReadThis(id)){//if user never read the book
      itGenre->second++;
    }
  }
  //update the authors the account likes
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

void Account::renewAccountBooks(){
  int numOfBooksRenewable = 0;
  //find out how many books can be renewed
  for(auto it = accountBooks.begin(); it != accountBooks.end(); ++it){
    if(it->second->getTimesRenewed() < 2){
      numOfBooksRenewable++;
    }
  }
  if(accountBooks.size() <= 0){//if account has no books checked out
    cout << "No books on this account." << endl;
  }else{//if account has books checked out
    cout << numOfBooksRenewable << " of " << accountBooks.size() << " books successfully renewed." << endl;
    int i = 1;
    //find out which books can be renewed and ewnew them
    for(auto it = accountBooks.begin(); it != accountBooks.end(); ++it, i++){
      if(it->second->getTimesRenewed() < 2){
        it->second->setDueDate( (it->second->getDueDate() + 5) );
  	it->second->setTimesRenewed( (it->second->getTimesRenewed() + 1) );
  	cout << "\t" << i << "." << endl;
  	it->second->printFullDescriptionNoId();
  	cout << "\tBook successfully renewed." << endl;
      }else{//if maximum checkout reached
        cout << "\t" << i << "." << endl;
  	it->second->printFullDescriptionNoId();
  	cout << "\tBook already renewed twice." << endl;
      }
    }
  }
}
//finds the two favorite genres for the account
//and pushes them to the @param vector<string>& twoGenres
void Account::twoFavoriteGenres(vector<string>& twoGenres){
  multimap<int, string> genresInOrder;
  for(auto it = genresRead.begin(); it != genresRead.end(); ++it){
    genresInOrder.insert(pair<int, string>(it->second, it->first));
  }
  if(genresInOrder.size() <= 0){//if user has not read any books
    return;
  }
   auto it = genresInOrder.end();
   --it;//end of the multimap
  if(genresInOrder.size() == 1){//if user has only read from 1 genre
    twoGenres.push_back(it->second);
  }else if(genresInOrder.size() >= 2){//if user has read from 2 or more genres
    twoGenres.push_back(it->second);//twoGenres[0] = most favorite
    --it;
    twoGenres.push_back(it->second);//twoGenres[1] = second most favorite
  }
}

string Account::favoriteAuthor(){
  multimap<int, string> authorsInOrder;
  for(auto it = authorsRead.begin(); it != authorsRead.end(); ++it){
    authorsInOrder.insert(pair<int, string>(it->second, it->first));
  }

  if(authorsInOrder.size() <= 0){
    return "";
  }
  auto it = authorsInOrder.end();
  --it;
  return it->second;
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
