#include "Machine.h"
#include <fstream>



Machine::Machine() {
    setName("Machine");
}

// 생성자
Machine::Machine(const int createdAt,const std::string& machineName, const int processTime, const int x, const int y)
        : createdAt(createdAt),machineName(machineName), processTime(processTime), x(x), y(y) {
            setName("Machine");
        }

// 소멸자
Machine::~Machine() {}

// machineName 반환 메서드
std::string Machine::getMachineName() const {
    return machineName;
}

// processTime 반환 메서드
int Machine::getProcessTime() const {
    return processTime;
}

int Machine::getCreatedAt() const{
    return createdAt;
}

bool Machine::getIsUse() const {
    return isUse;
}

void Machine::setIsUse(bool isUse) {
    this->isUse=isUse;
}

void Machine::handle(void* message) {
    if (message == nullptr) {
        std::cerr << "Invalid message" << std::endl;
        return;
    }
    Machine* machinePtr = reinterpret_cast<Machine*>(message);

    // Machine 객체의 이름 출력
    // std::cout << "Machine name: " << machinePtr->getMachineName() << std::endl;
    // std::cout << machinePtr->getOutputForInput("a");

    //하나의 부품을 통해 무언가 하나를 만드는 공정 이후 출력. 
    schedule(0, "Transducer", machinePtr);
    machinePtr->setIsUse(true);
}

void Machine::initialize() {
}

// Machine 객체의 리스트를 CSV 파일로 내보내는 정적 메서드
// void Machine::exportToCSV(const std::string& filename, const std::vector<Machine>& machines) {
//     std::ofstream file(filename);
//     file << "Machine Name,Process Time\n";  // CSV 헤더
//     for (const auto& machine : machines) {
//         file << machine.getMachineName() << ',' << machine.getProcessTime() << '\n';
//     }
//     file.close();
// }


void Machine::addInputOutputRule(const std::string& input, const std::string& output) {
    // 입력과 출력을 맵에 추가합니다.
    inputOutputRule[input] = output;
}

std::string Machine::getOutputForInput(const std::string& input) const {
    // 입력에 해당하는 출력을 찾습니다.
    auto it = inputOutputRule.find(input);
    if (it != inputOutputRule.end()) {
        // 맵에서 해당하는 값을 찾으면 반환합니다.
        return it->second;
    } else {
        // 입력에 해당하는 출력이 없을 경우 빈 문자열을 반환합니다.
        return "";
    }
}