#ifndef EOMODEL_H
#define EOMODEL_H

#include <string>
#include "SimEngine.h"
// 전방 선언
class SimEngine;
class EoModel {
private:
    SimEngine* engine;
    std::string name;

public:
    EoModel();
    virtual void initialize() = 0;
    virtual void handle(void* message) = 0;
    void schedule(int advance_time, std::string modelName, void* eventData);
    int getCurrentTime();
    void setName(std::string name);
    std::string getName();
};

#endif // EOMODEL_H
