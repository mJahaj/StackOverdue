## Assignment 3 - StackOverdue

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
The testing files provided in the `data/` folder can be used for some quick testing of this proogram. 
For example:

```
./StackOverdue data/library.small/books.data data/library.small/accounts.data
```

When the program first starts up you can type `HELP` for a list of commands to use. This is case sensitive and
all commands must be typed in uppercase.

If no book or account file is given, or the file names provided are not found, the program runs with no 
accounts or books. In this case you must add the books and accounts manually.

## Class Functionality


