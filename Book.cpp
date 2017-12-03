
#include "Book.h"

Book::Book(){
  borrowed = false;
  overdue = false;
  timesRenewed = 0;
  dueDate = 0;
  popularity = 0;
}

Book::Book(string titlE, string authoR, string genrE, int iD){
  title = titlE;
  author = authoR;
  genre = genrE;
  id = iD;
  borrowed = false;
  overdue = false;
  timesRenewed = 0;
  dueDate = 0;
  popularity = 0;
}

void Book::printShortDescription(){
  cout << "\"" << title <<"\""<< " by "<< author <<" "<< "(BookID# " << id <<") "
  << "[" << genre <<"]" <<". ";
  if(!borrowed){
  	cout << "AVAILIBLE."<< endl;
  }else{
  	cout <<"CHECKED OUT " <<"(AccountID# " << borrowerId << ")."<< endl;
  }
}

void Book::printFullDescription(){
  cout << "Title: " << "\"" << title <<"\"\n"
  << "Author: " << author << "\n"
  << "BookID#: " << id <<"\n"
  << "Genre: " << genre << "\n"
  << "Popularity Score: " << popularity <<"\n";
  if(!borrowed){
  	cout << "AVAILIBLE."<< endl;
  }else{
  	cout << "Borrower AccountID#: " << borrowerId << "\n"
  	<< "Due Date: " << dueDate <<"\n"
  	<< "Times Renewed: " << timesRenewed << "\n";
  	if(overdue){//-------------------------------------------------maybe func instead
  	  cout << "OVERDUE" << endl; 
  	}
  }
}

void Book::resetAfterReturn(){
  dueDate = 0;
  timesRenewed = 0;
  borrowerId = 0;
  borrowed = false;
  overdue = false;
}
//set the current borrweers ID and if it is unique increment popularity
void Book::setBorrowerId(int accountId){
  borrowerId = accountId;
  auto it = usersReadThis.find(accountId);
  if(it == usersReadThis.end()){
  	usersReadThis.insert(accountId);
  	popularity++;
  }
}

bool Book::userReadThis(int accId){
  auto it = usersReadThis.find(accId);
  if(it != usersReadThis.end()){
    return true;
  }
  return false;
}

istream& operator>>(istream& input, Book& book){
  string bookData = "";
  string token;
  char delim = '|';
  vector<string> tokens;

  getline(input, bookData);
  stringstream ss(bookData);
  while(getline(ss, token, delim)){
  	tokens.push_back(token);
  }

  stringstream strToIntId(tokens[0]);
  strToIntId >> book.id;
  book.title = tokens[1];
  book.author = tokens[2];
  book.genre = tokens[3];
  stringstream strToIntPopularity(tokens[4]);
  strToIntPopularity >> book.popularity;
  
  return input;
}