# Abstract Data Type: Dictionary
This project consists in the implementation of a dictionary on C++ using classes and it's divided into two implementations, which are:
+ **DAL** - _Dictionary with Array List_
+ **DSAL** - _Dictionary with Sorted Array List_
They both have it's own pros and cons, for example, an *DAL* for insertions has a complexity of *O(1)*, instead of *O(n)* on DSAL, otherwise, *DSAL* implement can manage a binary search while searching for a key, while *DAL* can't...

## Dependencies
On this project, it's primary language is **C++**, then, it's necessary `gcc` to compile and `make` to help on the compilation process. Also, can be useful to have `git` installed onto your system, since it can clone the entire repository with one simple command into terminal (`git clone https://github.com/FelipeCRamos/adt-dict.git `).

## Compilation
For compiling the project, first you will need to have all the source codes from this repository downloaded onto your PC/Mac. To do so, you can either `git clone` the repository or download the `.zip` file with all the source codes.

Once you're into the project folder, type on your unix/linux based system terminal:
```bash
make
```
Then, after compilation process ended, type `adt-dict` to run a driver code made for testing purposes.

## Authorship
Currently, this project is licensed with the ***MIT License***, and was entirely made by a computer science student at _UFRN_ named **Felipe Ramos**.
