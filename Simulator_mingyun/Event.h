#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
private:
    int time;           // 이벤트 발생 시간
    std::string modelName;   // 도착 모델의 이름
    void* message;      // 고객 객체

public:
    Event(int time, std::string modelName, void* message);

    int getTime();

    std::string getModelName();

    void* getMsgData();
};

#endif // EVENT_H
