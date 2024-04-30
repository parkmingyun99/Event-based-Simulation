#include "SimEngine.h"
#include <algorithm> // <algorithm> 헤더 파일 추가
#include <list>

SimEngine* SimEngine::instance = nullptr;

SimEngine::SimEngine() {
    modelMap = std::unordered_map<std::string, EoModel*>();
    eventQueue = std::priority_queue<Event*, std::vector<Event*>, std::function<bool(Event*, Event*)>>(
            [](Event* e1, Event* e2) { return e1->getTime() > e2->getTime(); });
}

SimEngine& SimEngine::getInstance() {
    if (instance == nullptr) {
        instance = new SimEngine();
    }
    return *instance;
}

void SimEngine::addModel(std::string name, EoModel* model) {
    if (name.empty()) {
        throw std::invalid_argument("Model name cannot be empty or null.");
    }

    if (modelMap.find(name) != modelMap.end()) {
        throw std::invalid_argument("Model with the same name already exists: " + name);
    }

    modelMap[name] = model;
}

void SimEngine::addModel(EoModel* model) {
    std::string modelName = model->getName();
    addModel(modelName, model);
}

EoModel* SimEngine::getModel(std::string name) {
    if (modelMap.find(name) != modelMap.end()) {
        return modelMap[name];
    }
    return nullptr;
}

void SimEngine::printAllModels() {
    std::cout << "Stored Models:" << std::endl;
    for (const auto& entry : modelMap) {
        std::string name = entry.first;
        EoModel* model = entry.second;
        std::cout << "Name: " << name << ", Model: " << model << std::endl;
    }
}

void SimEngine::run() {
    currentTime = 0; // 현재 시간은 0부터 시작.

    for (const auto& entry : modelMap) { // 이름과 모델이 저장된 해시맵 modelMap에서 하나씩 가져오기.
        EoModel* eoModel = entry.second;  // 이름과 모델이 저장돼있는데, second가 EoModel임.
        eoModel->initialize();
    }

    while (!eventQueue.empty() && currentTime <= endTime) {
        Event* currentEvent = eventQueue.top();
        eventQueue.pop();
        int eventTime = currentEvent->getTime();
        std::string modelName = currentEvent->getModelName();
        void* customer = currentEvent->getMsgData();

        if (currentTime < eventTime) {
            currentTime = eventTime;
        }

        if (modelMap.find(modelName) != modelMap.end()) {
            EoModel* model = modelMap[modelName];
            model->handle(customer);
        }

        delete currentEvent;
    }
}

void SimEngine::schedule(int advance_time, std::string modelName, void* eventData) {
    if (modelMap.find(modelName) == modelMap.end()) {
        throw std::invalid_argument("Model with name not found: " + modelName);
    }

    Event* event = new Event(currentTime + advance_time, modelName, eventData);
    eventQueue.push(event);
}



int SimEngine::getCurrentTime() {
    return currentTime;
}

void SimEngine::setEndTime(int endTime) {
    this->endTime = endTime;
}

void SimEngine::reset() {
    for (const auto& entry : modelMap) {
        delete entry.second;
    }
    modelMap.clear();
    while (!eventQueue.empty()) {
        delete eventQueue.top();
        eventQueue.pop();
    }
    currentTime = 0;
    endTime = INT_MAX;
    delete instance;
    instance = nullptr;
}
