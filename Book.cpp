
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

void Book::setCurrDate(int date){
  currDate = date;
  findIfOverdue();
}

void Book::findIfOverdue(){
  if(dueDate < currDate){
    overdue = true;
  }else{
    overdue = false;
  }
}

void Book::printShortDescription(){
  cout << "\"" << title <<"\""<< " by "<< author <<" "<< "(BookID# " << id <<") "
       << "[" << genre <<"]" <<". ";
  if(!borrowed){
    cout << "AVAILABLE."<< endl;
  }else{
    cout <<"CHECKED OUT " <<"(AccountID# " << borrowerId << ")."<< endl;
  }
}

void Book::printShortDescription2(){
  cout << "\"" << title <<"\""<< " by "<< author <<" "<< "(BookID# " << id <<") "
       << "[" << genre <<"]" <<". " << endl;
}

void Book::printFullDescription(){
  cout << "Title: " << "\"" << title <<"\"\n"
  << "Author: " << author << "\n"
  << "BookID#: " << id <<"\n"
  << "Genre: " << genre << "\n"
  << "Popularity Score: " << popularity <<"\n";
  if(!borrowed){
    cout << "AVAILABLE"<< endl;
  }else{
    cout << "Borrower AccountID#: " << borrowerId << "\n"
  	 << "Due Date: " << dueDate <<"\n"
  	 << "Times renewed: " << timesRenewed << "\n";
    if(overdue){//-------------------------------------------------maybe func instead
      cout << "OVERDUE" << endl; 
    }
  }
}

void Book::resetAfterReturn(){
  dueDate = 0;
  timesRenewed = 0;
  borrowerId = -1;
  borrowed = false;
  overdue = false;
  currBorrowerAccount = NULL;
}
//
void Book::setBorrowerId(int accountId, Account* whoBorrowed){
  currBorrowerAccount = whoBorrowed;
  borrowerId = accountId;
  borrowed = true;
  auto it = usersReadThis.find(accountId);
  if(it == usersReadThis.end()){
   usersReadThis.insert(accountId);
   popularity++;
  }
  overdue = false;
}

bool Book::userReadThis(int accId){
  auto it = usersReadThis.find(accId);
  if(it != usersReadThis.end()){
    return true;
  }
  return false;
}

void Book::printFullDescriptionNoId(){
  cout << "\tTitle: " << "\"" << title <<"\"" << endl;
  cout << "\tAuthor: " << author << endl;
  cout << "\tBookID#: " << id << endl;
  cout << "\tGenre: " << genre << endl;
  cout << "\tPopularity Score: " << popularity << endl;
  cout << "\tDue Date: " << dueDate << endl;
  cout << "\tTimes renewed: " << timesRenewed << endl;
  if(overdue){//-------------------------------------------------maybe func instead
    cout << "\tOVERDUE" << endl; 
  }
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
