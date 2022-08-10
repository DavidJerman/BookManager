#include "author.h"

const int Author::getID() const
{
    return ID;
}

void Author::setID(const int newID)
{
    ID = newID;
}

const std::string &Author::getName() const
{
    return name;
}

void Author::setName(const std::string &newName)
{
    name = newName;
}

const std::string &Author::getBirthDate() const
{
    return birthDate;
}

void Author::setBirthDate(const std::string &newBirthDate)
{
    birthDate = newBirthDate;
}

const std::string &Author::getBiography() const
{
    return biography;
}

void Author::setBiography(const std::string &newBiography)
{
    biography = newBiography;
}

Author::Author(const std::string name, const std::string birthDate,
               const std::string biography, int ID)
    : name(std::move(name)), birthDate(std::move(birthDate)),
      biography(std::move(biography)), QString(QString::fromStdString(name)) {
    this->ID = ID;
}

