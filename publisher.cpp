#include "publisher.h"

const int Publisher::getID() const
{
    return ID;
}

void Publisher::setID(const int newID)
{
    ID = newID;
}

const std::string &Publisher::getName() const
{
    return name;
}

void Publisher::setName(const std::string &newName)
{
    name = newName;
}

const std::string &Publisher::getTaxID() const
{
    return taxID;
}

void Publisher::setTaxID(const std::string &newTaxID)
{
    taxID = newTaxID;
}

Publisher::Publisher(const std::string name, const std::string taxID, int ID)
    : name(std::move(name)), taxID(std::move(taxID)), ID(ID), QString(QString::fromStdString(name)) {}
