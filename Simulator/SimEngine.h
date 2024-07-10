#ifndef SIMENGINE_H
#define SIMENGINE_H

#include <unordered_map>
#include <queue>
#include <functional>
#include <iostream>
#include <stdexcept>
#include "Event.h"
#include "EoModel.h"

// 전방 선언
class EoModel;
class SimEngine {
private:
    static SimEngine* instance; // 싱글톤 인스턴스
    std::unordered_map<std::string, EoModel*> modelMap; // 이름과 모델을 저장하는 HashMap
    std::priority_queue<Event*, std::vector<Event*>, std::function<bool(Event*, Event*)>> eventQueue; // 이벤트 큐
    int currentTime = 0;
    int endTime = INT_MAX;

    // private 생성자
    SimEngine();

public:
    // 싱글톤 인스턴스 반환 메서드
    static SimEngine& getInstance();

    // 이름과 모델을 HashMap에 저장하는 메서드
    void addModel(std::string name, EoModel* model);
    void addModel(EoModel* model);

    // 이름을 사용하여 모델을 검색하는 메서드
    EoModel* getModel(std::string name);

    // 모든 모델을 출력하는 메서드 (예시용)
    void printAllModels();

    void run();

    void schedule(int advance_time, std::string modelName, void* eventData);

    int getCurrentTime();

    void setEndTime(int endTime);

    void reset();
};

#endif // SIMENGINE_H
