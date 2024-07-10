#include "EoModel.h"

EoModel::EoModel() {
    engine = &SimEngine::getInstance();
}

void EoModel::initialize() {
    // Implementation
}

void EoModel::schedule(int advance_time, std::string modelName, void* eventData) {
    engine->schedule(advance_time, modelName, eventData);
}

int EoModel::getCurrentTime() {
    return engine->getCurrentTime();
}

void EoModel::setName(std::string name) {
    this->name = name;
}

std::string EoModel::getName() {
    return this->name;
}
