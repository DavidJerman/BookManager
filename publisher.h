#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include <QString>

class Publisher : public QString
{
private:
    int ID;
    std::string name;
    std::string taxID;
public:
    Publisher(const std::string name, const std::string taxID,
              int ID = 0);

    const int getID() const;
    void setID(const int newID);
    const std::string &getName() const;
    void setName(const std::string &newName);
    const std::string &getTaxID() const;
    void setTaxID(const std::string &newTaxID);
};

#endif // PUBLISHER_H
