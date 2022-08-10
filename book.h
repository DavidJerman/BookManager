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

    std::string getISBN() const;

    int getYearOfRelease() const;

    int getRating() const;

    int getAuthor() const;

    int getPublisher() const;


    void setTitle(const std::string &newTitle);

    void setSynopsis(const std::string &newSynopsis);

    void setISBN(const std::string &newISBN);

    void setYearOfRelease(int newYearOfRelease);

    void setRating(int newRating);

    void setAuthor(int newAuthor);

    void setPublisher(int newPublisher);


};

#endif // BOOK_H
