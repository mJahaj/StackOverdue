
#include "LibraryBooks.h"

LibraryBooks::LibraryBooks(){
  largestBookId = 0;
}

LibraryBooks::~LibraryBooks(){
  for(auto it = books.begin(); it != books.end(); ++it){
    delete it->second;
  }
}

istream& operator>>(istream& bookFile, LibraryBooks& bookS){
  bookFile >> bookS.bookCount;
  string consumeEmpty;
  getline(bookFile, consumeEmpty);

  for(int i = 0; i < bookS.bookCount; i++){
    Book* newBook = new Book;
    bookFile >> *newBook;
    //keep track of largest id
    if(newBook->getId() > bookS.largestBookId){
      bookS.largestBookId = newBook->getId();
    }
    bookS.books.emplace(newBook->getId(), newBook);
  }
  return bookFile;
}

void LibraryBooks::printAllById(){
  int i = 1;
  for(auto it = books.begin(); it != books.end(); ++it, i++){
    cout << i << ". ";  
    it->second->printShortDescription();
  }
}

void LibraryBooks::printAllByTitle(){
  multimap<string, Book*> sortTitle;
  //order the books by title ascending alphabecical
  for(auto it = books.begin(); it != books.end(); ++it){
    sortTitle.insert(pair<string, Book*>(it->second->getTitle(), it->second));
  }
  int i = 1;
  for(auto it = sortTitle.begin(); it != sortTitle.end(); ++it, i++){
    cout << i << ". ";
    it->second->printShortDescription();
  }
}

void LibraryBooks::printAllByAuthor(){
  multimap<string, Book*> sortAuthor;
  //order the books by author ascending alphabecical
  for(auto it = books.begin(); it != books.end(); ++it){
    sortAuthor.insert(pair<string, Book*>(it->second->getAuthor(), it->second));
  }
  int i = 1;
  for(auto it = sortAuthor.begin(); it != sortAuthor.end(); ++it, i++){
    cout << i << ". ";
    it->second->printShortDescription();
  }
}

void LibraryBooks::printAllByGenre(){
  multimap<string, Book*> sortGenre;
  //order the books by genre ascending alphabecical
  for(auto it = books.begin(); it != books.end(); ++it){
    sortGenre.insert(pair<string, Book*>(it->second->getGenre(), it->second));
  }
  int i = 1;
  for(auto it = sortGenre.begin(); it != sortGenre.end(); ++it, i++){
    cout << i << ". ";
    it->second->printShortDescription();
  }
}

void LibraryBooks::printAllByPopularity(){
  multimap<int, Book*> sortPopularity;
  //order the books by popularity score ascending
  for(auto it = books.begin(); it != books.end(); ++it){
    sortPopularity.insert(pair<int, Book*>(it->second->getPopularity(), it->second));
  }
  int i = 1;
  //print the books with popularity score descending
 for(auto it = sortPopularity.rbegin(); it != sortPopularity.rend(); ++it, i++){
   cout << i << ". ";  
   it->second->printShortDescription();
 }
}
//prints all of the books containing the param phrase
void LibraryBooks::searchByTitlePhrase(string phrase){
  bool found = false;
  int i = 0;
  for(auto it = books.begin(); it != books.end(); ++it){
    if(foundPhrase(phrase, it->second->getTitle())){
      found = true;
      if(found && i == 0){
        cout << "Search Results:" << endl;
      }
      i++;
      cout << i <<". ";
      it->second->printShortDescription();
    }
  }
  if(!found){
    cout << "No search results found." << endl;
  }
}
//prints all of the books containing the param phrase
void LibraryBooks::searchByAuthorPhrase(string phrase){
  bool found = false;
  int i = 0;
  for(auto it = books.begin(); it != books.end(); ++it){
    if(foundPhrase(phrase, it->second->getAuthor())){
      found = true;
      if(found && i == 0){
        cout << "Search Results:" << endl;
      }
      i++;
      cout << i <<". ";
      it->second->printShortDescription();
    }
  }
  if(!found){
    cout << "No search results found." << endl;
  }
}

void LibraryBooks::addBook(){
  string title;
  string author;
  string genre;
  
  cout << "Enter the new book's title." << endl;
  cout << "> ";
  getline(cin, title);

  cout << "Enter the new book's author." << endl;
  cout << "> ";
  getline(cin, author);

  cout << "Enter the new book's genre." << endl;
  cout << "> ";
  getline(cin, genre);
  //make sure the books does not already exist in the library
  if(bookAlreadyExists(title, author)){
    cout <<"Book with this title and author already exists." << endl;
  }else{//if the book is not already in the library
    largestBookId++; 
    Book* newBook = new Book(title, author, genre, largestBookId);
    books.insert(std::pair<int, Book*> (largestBookId, newBook));
    cout << "BookID# " << largestBookId <<" successfully created." << endl;
  }
}

bool LibraryBooks::giveBookUnconditional(int bookID, Book*& tempBook){
  auto it = books.find(bookID);
  if(it == books.end()){
    return false;
  }
  tempBook = it->second;
  return true;
}

void LibraryBooks::giveBookConditional(Account* givetoThisAcc, int bookId, int currTime){
  //find if book exists
  auto it = books.find(bookId);
  if(it == books.end()){
    cout << "BookID# " << bookId << " not found." << endl;
    return;
  }else if(it->second->getBorrowed()){
    cout << "Book is already checked out." << endl;
    return;
  }

  if(givetoThisAcc->numOfBooksOverdue() > 0){
    cout << "Account has books overdue." << endl;
    return;
  }else if(givetoThisAcc->getNumOfBooks() >= 10){
    cout << "Account already has 10 books checked out." << endl;
    return;
  }else{
    givetoThisAcc->takeBook(it->second);
    it->second->setDueDate(currTime + 15);
    it->second->setBorrowerId(givetoThisAcc->getAccountId(), givetoThisAcc);
    cout << "Book successfully checked out." << endl;
    cout << "Title: \"" << it->second->getTitle() << "\"" << endl;
    cout << "Author: " << it->second->getAuthor() << endl;
    cout << "BookID#: " << it->second->getId() << endl;
    cout << "Genre: " << it->second->getGenre() << endl;
    cout << "Popularity Score: " << it->second->getPopularity() << endl;
    cout << "Borrower AccountID#: " << givetoThisAcc->getAccountId() << endl;
    cout << "Due Date: " << it->second->getDueDate() << endl;
    cout << "Times renewed: " << it->second->getTimesRenewed() << endl; 
  }
}

void LibraryBooks::setBooksCurrDate(int date){
  for(auto it = books.begin(); it != books.end(); ++it){
    it->second->setCurrDate(date);
  }
}

void LibraryBooks::browse(){
  if(books.size() <= 0){
    cout << "No books in your library." << endl;
    return;
  }
  string criteria = "";
  cout << "Enter the criteria to sort by. (title/author/genre/bookid/popularity)" << endl;
  cout << "> ";
  getline(cin, criteria);

  if(criteria == "title"){
    printAllByTitle();
  }else if(criteria == "author"){
    printAllByAuthor();
  }else if(criteria == "genre"){
    printAllByGenre();
  }else if(criteria == "bookid"){
    printAllById();
  }else if(criteria == "popularity"){
    printAllByPopularity();
  }else{
    cout << "Invalid value." << endl;
  }
}

void LibraryBooks::printSpecificBook(){
  string userInput;
  cout << "Enter the book id." << endl;
  cout << "> ";
  getline(cin, userInput);
  
  if(!isValidInt(userInput) || userInput == ""){
    cout << "Invalid input." << endl;
  }else{
    auto it = books.find(stoi(userInput));
    if(it == books.end()){
      cout << "BookID# " << userInput << " not found." << endl;
    }else{
      it->second->printFullDescription();
    }
  }
}

void LibraryBooks::searchByPhrase(){
  cout << "Enter the criteria to search by. (title/author)" << endl;
  string userInput;
  string phraseInput;
  cout << "> ";
  getline(cin, userInput);
  
  cout << "Enter the search phrase.\n> ";
  if(userInput == "title"){
    getline(cin, phraseInput);
    searchByTitlePhrase(phraseInput);
  }else if(userInput == "author"){
    getline(cin, phraseInput);
    searchByAuthorPhrase(phraseInput);
  }else{
    cout << "Invalid value." << endl;
  }
}

void LibraryBooks::exportBooks(string expFile){
  ofstream outputBookFileHandle;
  outputBookFileHandle.open(expFile);
  outputBookFileHandle << books.size() << endl;

  for(auto it = books.begin(); it != books.end(); ++it){
    outputBookFileHandle << it->second->getId() << "|" << it->second->getTitle()
    << "|" << it->second->getAuthor() << "|" << it->second->getGenre() << "|" 
    << it->second->getPopularity();
  }
  
  cout << "Books data successfully exported to \"" << expFile << "\"." << endl;
  outputBookFileHandle.close();
}

int LibraryBooks::numOfBooksOverdue(){
  int accum = 0;
  for(auto it = books.begin(); it != books.end(); ++it){
    if(it->second->isOverdue() && it->second->getBorrowed()){
      accum++;
    }
  }
  return accum;
}

void LibraryBooks::removeBook(){
  string userInput = "";
  cout << "Enter the book id." << endl;
  cout << "> ";
  getline(cin, userInput);

  if(!isValidInt(userInput) || userInput == ""){
    cout << "Invalid input." << endl;
  }else{
    auto it = books.find(stoi(userInput));
    if(it == books.end()){
      cout << "BookID# " << userInput << " not found." << endl;
    }else{
      if(!it->second->getBorrowed()){//if book is not borrowed
        cout << "\"" << it->second->getTitle() << "\" by " << it->second->getAuthor()
        << " successfully removed." << endl;
        books.erase(it);
      }else{//if book is borrowed, force return the book from the account
        Account* tempAcc = it->second->getCurrAccountBorrower();
        cout << "Force returning book from AccountID# " << tempAcc->getAccountId() << "." << endl;
        tempAcc->returnSpecifiedBook(stoi(userInput));//remove book from account
        cout << "\"" << it->second->getTitle() << "\" by " << it->second->getAuthor() 
          << " successfully removed." << endl; 
        delete it->second;
        books.erase(it);
      } 
    }
  }
}

void LibraryBooks::returnBook(int currDate){
  string userInput = "";
  cout << "Enter the book id." << endl; 
  cout << "> ";
  getline(cin, userInput);
  
  if(!isValidInt(userInput) || userInput == ""){
    cout << "Invalid input." << endl;
  }else{
    auto it = books.find(stoi(userInput));
    if(it == books.end()){
      cout << "BookID# " << userInput << " not found." << endl;
    }else{
      if(!it->second->getBorrowed()){
        cout << "Book is currently not checked out." << endl;
      }else{
        Account* tempAcc = it->second->getCurrAccountBorrower();
        cout << "Book successfully returned from AccountID# " << tempAcc->getAccountId() << " ";
        if(!it->second->isOverdue()){
          cout << "(on time)." << endl;
        }else{
          cout << "(overdue by " << (currDate - it->second->getDueDate())<< " days)." << endl;
        }
        tempAcc->returnSpecifiedBook(stoi(userInput));
      }
    }
  }  
}

void LibraryBooks::giveBookRecommendation(vector<string>& genres, string author, int accId){
  unordered_map<int, Book*> alreadyRecommended;
  multimap<int, Book*> byMostFavoriteGenre;
  multimap<int, Book*> by2ndMostFavoriteGenre;
  multimap<int, Book*> byAuthorFavorite;
  
    //find books with most favorite genre that have not been read
  for(auto it = books.begin(); it != books.end(); ++it){
    if(it->second->getGenre() == genres[0] && !(it->second->userReadThis(accId))){
      byMostFavoriteGenre.insert(pair<int, Book*>(it->second->getPopularity(), it->second));
    }
  }
  if(byMostFavoriteGenre.size() == 1){//if only 1 recommendation was found
    cout << "You love " << genres[0]<< ". We recommend:" << endl;
    cout << "1. ";
    auto it = byMostFavoriteGenre.begin();
    it->second->printShortDescription();
    alreadyRecommended.insert(pair<int, Book*>(it->second->getId(), it->second));
  }else if(byMostFavoriteGenre.size() >= 2){//if more than 1 recommendation was found
    cout << "You love " << genres[0]<< ". We recommend:" << endl;
    cout << "1. ";
    auto it = byMostFavoriteGenre.end();
    --it;//most popular book
    it->second->printShortDescription();
    alreadyRecommended.insert(pair<int, Book*>(it->second->getId(), it->second));
    --it;//second most popular book
    cout << "2. ";
    it->second->printShortDescription();
    alreadyRecommended.insert(pair<int, Book*>(it->second->getId(), it->second));
  }
  //if there is a second genre to consider for recommending
  if(genres.size() >= 2){
    //find all possible books with second most favorite genre that have not been read or recommended
    for(auto it = books.begin(); it != books.end(); ++it){
      if(it->second->getGenre() == genres[1] && !(it->second->userReadThis(accId))){
        auto is = alreadyRecommended.find(it->second->getId());
        if(is == alreadyRecommended.end()){//check if its not already recommended
          by2ndMostFavoriteGenre.insert(pair<int, Book*>(it->second->getPopularity(), it->second));
        }
      }
    }

    if(by2ndMostFavoriteGenre.size() == 1){//if only 1 recommendation was found
      cout << "You love " << genres[1]<< ". We recommend:" << endl;
      cout << "1. ";
      auto it = by2ndMostFavoriteGenre.begin();
      it->second->printShortDescription();
      alreadyRecommended.insert(pair<int, Book*>(it->second->getId(), it->second));
    }else if(by2ndMostFavoriteGenre.size() >= 2){//if more than 1 recommendation was found
      cout << "You love " << genres[1]<< ". We recommend:" << endl;
      cout << "1. ";
      auto it = by2ndMostFavoriteGenre.end();
      --it;//most popular book
      it->second->printShortDescription();
      alreadyRecommended.insert(pair<int, Book*>(it->second->getId(), it->second));
      --it;//second most popular book
      cout << "2. ";
      it->second->printShortDescription();
      alreadyRecommended.insert(pair<int, Book*>(it->second->getId(), it->second));
    }

  }
    //find books with the favorite author that have not been read or recommended
    for(auto it = books.begin(); it != books.end(); ++it){
      if(it->second->getAuthor() == author && !(it->second->userReadThis(accId))){
        auto is = alreadyRecommended.find(it->second->getId());
        if(is == alreadyRecommended.end()){//check if its not already recommended
          byAuthorFavorite.insert(pair<int, Book*>(it->second->getPopularity(), it->second));
        }
      }
    }
    cout << author << endl;
    if(byAuthorFavorite.size() >= 1){
      cout << "You love " << author << ". We recommend:" << endl;
      auto it = byAuthorFavorite.end();
      cout << "1. ";
      --it;
      it->second->printShortDescription();  
    }
}

//-------------------Helper Functions----------------------------
bool LibraryBooks::foundPhrase(string phrase, string str){
  std::size_t found = str.find(phrase);
  
  if (found!=std::string::npos){
     return true;
  }
  return false;
}
//currently not used
int LibraryBooks::generateId(){
  if(books.size() <= 0){
    return 1;
  }else{
    auto it = books.end();
    --it;
    int newId = it->first;
    newId++;
    return newId;
  }
}
//this function searches the entire list of books to find a match
//for title and author, if found it will return true
bool LibraryBooks::bookAlreadyExists(string titlE, string authoR){
  if(books.size() <= 0){
    return false;
  }
    for(auto it = books.begin(); it != books.end(); ++it){
      if(it->second->getTitle() == titlE && it->second->getAuthor() == authoR){
        return true;
      }
    }
  
  return false;
}
//First the function makes sure the only character is not '-'
//and then iterates through each char in the string
//if a char is not an int return false
bool LibraryBooks::isValidInt(string str){
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
