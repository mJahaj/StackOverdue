## Assignment 3 - StackOverdue

Mariglen Jahaj

## Background

Ever wondered why checking out the books at your local library always took so long? A quick peek at
the management system’s codebase revealed years of mismanaged pointers, virtually no
documentation, and the homogenous use of only the vector data structure. It was horrible! The library
staff put up with it for a long time, but one day, the developers accidentally deleted the whole
application. With no backups! They weren’t even using git!

Fortunately for you, this was the last straw for the librarians. It was time for a new era of library
management software. The possibilities are endless. You’re hired as the new developer. Armed with a
firm knowledge of puns, data structures, and algorithms, you set forth to create StackOverdue. This
time, you’re definitely going to use git.


### Compiling and Executing
Compiling program with:
```
make
```
The compiled exe can take no argument, one argument, or two arguments in the specified order:
```
./StackOverdue <Books file name> <Accounts file name>
```
NOTE: The order in which you enter the books file and accounts file is final, you cannot enter the account 
file before the book file.  

The testing files provided in the `data/` folder can be used for some quick testing of this proogram. 
For example:

```
./StackOverdue data/library.small/books.data data/library.small/accounts.data
```

When the program first starts up you can type `HELP` for a list of commands to use. This is case sensitive and
all commands must be typed in uppercase. All other input prompts are also case sensitive and you must enter it
the way it is shown on screen. Ex.(name/accountid/checkouts).

If no book or account file is given, or the file names provided are not found, the program runs with no 
accounts or books. In this case you must add the books and accounts manually.

## Design Description

#### Book

This class represents a single library book. This class has functionality to print the books description, return the books data (title, author, id, popularity, due date, times renewed). Book class also uses a unordered_set<int> to keep track of the account id's that have checked out this book. This set is used for properly incrementing the books popluarity. I chose unordered_set because the id's do not need to be ordered and finding or insearting an id can be average case O(1) or O(n) worst case. Book also forward declares the class `Account`. Forwarding `Account` allows this class to hold and return a pointer of the current borrower of the book.


#### Account

This class represents a single user account. It contains functionality to print a short and full description of the account, return the accounts data (name, id, number of books currently checked out). Account class uses an unordered_map<int id,Book*> to hold the current books that the account has checked out. I chose an unordered_map because the books do not need to be sorted and finding or insearting a book can be average case O(1) and worst case O(n). Account also has functionality to recieve a book from the library, return a book, return all books and renew all of books checked out. Account also has functionality to return the first and second most favorite genre and most favorite author. An unordered_map<string genre, int timesRead> is used to keep track of which genres the user has checked out and how many times they read from this genre. And similarly an unordered_map is used in the same way to keep track of the authors read from. I chose an unordered_map for both genres and authors because they do not need to be ordered alphabetically which makes inserting a new author or genre as fast s O(1) average case and O(n) worst case. 


#### LibraryBooks 

This class is used to represent all of the books in the library. It contains functionality to print a short description of all of the books based on (id number, title, genre, author, popularity), print the full description
of a specified book, search and print a short description of all the books containing a phrase in the author or title of the book. Functionality also includes adding a new book, deleting a book, receiving a returned book. For giving a book to an account there are two functions giveBookUnconditional() which gives a book to an account being loaded from a file inwhich we assume the account has no blocks. And giveBookConditional() which makes sure the account does not have overdue books or ten books already checked out. And finally LibraryBooks can also export the books to a file and give book recomendations. LibraryBooks uses a map<int id, Book*> to hold all of the books. Although a unordered_map could be used to store the Book*, the unordered_map has a worst case O(n) to add or remove a book while a map has a worst case of O(log n) to insert or remove. The unordered_map is better in the average case O(1) but for the purpose of learning the tools I chose map as the underlying data structure.

NOTE: The functions that print a short description of a book based on the ordering (title, genre, author, popularity), use a multimap for sorting. The algorithm `sort` could also be used in place of the multimap but in  either case for printing all books in a specified order the time complexity is O(n log(n)).

### StackOverdue 

This class is the library system manager. StackOverdue uses a `LibraryBooks` object to communicate with the books in the library. It also contains a map<int, Account*> to hold all of the accounts ordered by id number. I chose a map to keep the accounts ordered by id to print the accounts by id without needing to sort. For adding, searching or removing the worst case is O(log n), but an unordered_map would have been better in the average case O(1) but worse in the worst case O(n). On startup this class reads from the provided books and accounts files, and loads the accounts and library. For the accounts this class contains functionality to add an account, remove an account, print a short description of all the accounts, print a full description for a specific account, print all the accounts ordered by (name alphabetical ascending, number of checkouts descending, id number ascending), request a book for an account, request book recommendations for an account, and renew all books in an account. For the Library system altogether StackOverdue has functionality to request command input from the user, display a list of commands, export the accounts and library to their seperate files, move forward in time, and display system diagnostics.

NOTE: The functions for printing a short description of all the accounts by (name, checkouts) use a multimap for sorting. Using the `sort` function required to transfer the account pointers to a vector and perform the sorting, the time complexity for `sort` is O(n log(n)). And sorting with the multimap takes the same amount of time 
O(n log(n)) because we enter each book into the multimap that takes O(log(n)) for each book. The only difference is that multimap might take a little more memory to hold the key value, while the `sort` using a vector does not require a key.

## Optimizing

I made a mistake to start the assignment before having my design graded. The StackOverdue could have been better designed by making a seperate Account manager class. And also seperating the commands I/O from the actual logic or the command. The StackOverdue and LibraryBooks implementation files became too long and it became difficult to handle as the code got longer. I learned my lesson and I see why the design is more important and takes more time than actually coding.

