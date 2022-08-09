#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
private:
    std::string title;
    std::string synopsis;
    std::string ISBN;
    int yearOfRelease;
    int rating;
    int author;
    int publisher;

public:
    Book(std::string title, std::string synopsis, std::string ISBN, int yearOfRelease,
         int rating, int author, int publisher);

    std::string getTitle() const;

    std::string getSynopsis() const;
};

#endif // BOOK_H
