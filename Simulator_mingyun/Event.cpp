#include "Event.h"

Event::Event(int time, std::string modelName, void* message) {
    this->time = time;
    this->modelName = modelName;
    this->message = message;
}

int Event::getTime() {
    return time;
}

std::string Event::getModelName() {
    return modelName;
}

void* Event::getMsgData() {
    return message;
}
