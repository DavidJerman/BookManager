#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
#include <QString>

class Author : public QString
{
private:
    int ID;
    std::string name;
    std::string birthDate;
    std::string biography;
public:
    Author(const std::string name, const std::string birthDate,
           const std::string biography, int ID = 0);

    const int getID() const;
    void setID(const int newID);
    const std::string &getName() const;
    void setName(const std::string &newName);
    const std::string &getBirthDate() const;
    void setBirthDate(const std::string &newBirthDate);
    const std::string &getBiography() const;
    void setBiography(const std::string &newBiography);
};

#endif // AUTHOR_H
