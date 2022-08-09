#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message
{
private:
    int status;
    std::string message;
public:
    Message(int status, std::string message);

    std::string getMessage();
    int getStatus();
};

#endif // MESSAGE_H
