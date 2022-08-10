#include "book.h"


Book::Book(std::string title, std::string synopsis, std::string ISBN, int yearOfRelease,
           int rating, int author, int publisher)
    : title(std::move(title)), synopsis(std::move(synopsis)), ISBN(std::move(ISBN)),
      yearOfRelease(yearOfRelease), rating(rating), author(author), publisher(publisher) {}

std::string Book::getTitle() const
{
    return this->title;
}

std::string Book::getSynopsis() const
{
    return this->synopsis;
}

std::string Book::getISBN() const
{
    return this->ISBN;
}

int Book::getYearOfRelease() const
{
    return this->yearOfRelease;
}

int Book::getRating() const
{
    return this->rating;
}

int Book::getAuthor() const
{
    return this->author;
}

int Book::getPublisher() const
{
    return this->publisher;
}

void Book::setTitle(const std::string &newTitle)
{
    title = newTitle;
}

void Book::setSynopsis(const std::string &newSynopsis)
{
    synopsis = newSynopsis;
}

void Book::setISBN(const std::string &newISBN)
{
    ISBN = newISBN;
}

void Book::setYearOfRelease(int newYearOfRelease)
{
    yearOfRelease = newYearOfRelease;
}

void Book::setRating(int newRating)
{
    rating = newRating;
}

void Book::setAuthor(int newAuthor)
{
    author = newAuthor;
}

void Book::setPublisher(int newPublisher)
{
    publisher = newPublisher;
}
