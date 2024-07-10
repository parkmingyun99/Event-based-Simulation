#include "Transducer.h"
#include "Machine.h"
#include <iostream>

int Transducer::totalSpendTime = 0; // 정적 멤버 변수 초기화

Transducer::Transducer() {
    setName("Transducer");
    this->totalSpendTime=0;
}

void Transducer::handle(void* message) {
    if (message == nullptr) {
        std::cerr << "Invalid message received." << std::endl;
        return;
    }

    // message를 Machine 포인터로 안전하게 캐스팅
    Machine* machine = reinterpret_cast<Machine*>(message);
    
    // 현재 시간과 생성 시간을 가져와 계산
    int currentTime = machine->getCurrentTime();
    int createdAt = machine->getCreatedAt();
    int elapsedTime = currentTime - createdAt;

    std::cout << machine->getMachineName() << "is spent " << elapsedTime << " units of time." << std::endl;

}

void Transducer::initialize() {
}