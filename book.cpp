#include "book.h"

Book::Book(std::string title, std::string synopsis, std::string ISBN, int yearOfRelease,
           int rating, int author, int publisher)
    : title(std::move(title)), synopsis(std::move(synopsis)), ISBN(std::move(ISBN)),
      yearOfRelease(yearOfRelease), rating(rating), author(author), publisher(publisher) {}

