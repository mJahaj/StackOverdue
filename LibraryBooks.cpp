
#include "LibraryBooks.h"

LibraryBooks::LibraryBooks(){
  largestBookId = 0;
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

  for(auto it = books.begin(); it != books.end(); ++it){
  	sortPopularity.insert(pair<int, Book*>(it->second->getPopularity(), it->second));
  }
  int i = 1;
 for(auto it = sortPopularity.rbegin(); it != sortPopularity.rend(); ++it, i++){
   cout << i << ". ";  
   it->second->printShortDescription();
 }
}

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

  if(bookAlreadyExists(title, author)){
    cout <<"Book with this title and author already exists." << endl;
  }else{
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
  
  if(!isValidInt(userInput)){
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
//-------------------Helper Functions----------------------------
bool LibraryBooks::foundPhrase(string phrase, string str){
  std::size_t found = str.find(phrase);
  
  if (found!=std::string::npos){
     return true;
  }
  return false;
}

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