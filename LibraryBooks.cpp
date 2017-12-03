
#include "LibraryBooks.h"


istream& operator>>(istream& bookFile, LibraryBooks& bookS){
  bookFile >> bookS.bookCount;
  string consumeEmpty;//---------------------------------------
  getline(bookFile, consumeEmpty);

  for(int i = 0; i < bookS.bookCount; i++){
    Book* newBook = new Book;
    bookFile >> *newBook;
    bookS.books.emplace(newBook->getId(), newBook);
  }
  return bookFile;
}

void LibraryBooks::printAllById(){
  for(auto it = books.begin(); it != books.end(); ++it){
  	it->second->printShortDescription();
  }
}

void LibraryBooks::printAllByTitle(){
  multimap<string, Book*> sortTitle;

  for(auto it = books.begin(); it != books.end(); ++it){
  	sortTitle.insert(pair<string, Book*>(it->second->getTitle(), it->second));
  }

  for(auto it = sortTitle.begin(); it != sortTitle.end(); ++it){
  	it->second->printShortDescription();
  }
}

void LibraryBooks::printAllByAuthor(){
  multimap<string, Book*> sortAuthor;

  for(auto it = books.begin(); it != books.end(); ++it){
  	sortAuthor.insert(pair<string, Book*>(it->second->getAuthor(), it->second));
  }

  for(auto it = sortAuthor.begin(); it != sortAuthor.end(); ++it){
  	it->second->printShortDescription();
  }
}

void LibraryBooks::printAllByGenre(){
  multimap<string, Book*> sortGenre;

  for(auto it = books.begin(); it != books.end(); ++it){
  	sortGenre.insert(pair<string, Book*>(it->second->getGenre(), it->second));
  }

  for(auto it = sortGenre.begin(); it != sortGenre.end(); ++it){
  	it->second->printShortDescription();
  }
}

void LibraryBooks::printAllByPopularity(){
  multimap<int, Book*> sortPopularity;

  for(auto it = books.begin(); it != books.end(); ++it){
  	sortPopularity.insert(pair<int, Book*>(it->second->getPopularity(), it->second));
  }

 for(auto it = sortPopularity.rbegin(); it != sortPopularity.rend(); ++it){
   it->second->printShortDescription();
 }
}

void LibraryBooks::searchByTitlePhrase(string phrase){
  bool found = false;
  
  for(auto it = books.begin(); it != books.end(); ++it){
  	if(foundPhrase(phrase, it->second->getTitle())){
  	  found = true;
  	  it->second->printShortDescription();
  	}
  }
  if(!found){
  	cout << "No search results found." << endl;
  }

}

void LibraryBooks::searchByAuthorPhrase(string phrase){
  bool found = false;
  
  for(auto it = books.begin(); it != books.end(); ++it){
  	if(foundPhrase(phrase, it->second->getAuthor())){
  	  found = true;
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
    int newBookId = generateId();
    Book* newBook = new Book(title, author, genre, newBookId);
    books.insert(std::pair<int, Book*> (newBookId, newBook));
    cout << "BookID# " << newBookId <<" successfully created." << endl;
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