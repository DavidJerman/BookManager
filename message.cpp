#include "message.h"

Message::Message(int status, std::string message) : status(status), message(std::move(message)) {}

std::string Message::getMessage() {
    return this->message;
}

int Message::getStatus() {
    return this->status;
}
