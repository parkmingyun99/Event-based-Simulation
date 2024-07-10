#include "Machine.h"
#include <fstream>



Machine::Machine() {
    setName("Machine");
}

// 생성자
Machine::Machine(const int createdAt, const std::string& machineName, const int processTime, const Position& position)
    : createdAt(createdAt), machineName(machineName), processTime(processTime), position(position) {
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

Position Machine::getPosition() const {
    return position;
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

    // 머신 이름과 인벤토리 출력
    std::cout << "Machine: " << machinePtr->getMachineName() << std::endl;
    std::cout << "Inventory:" << std::endl;
    for (const auto& pair : machinePtr->inventory) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }

    // 1. 머신이 가진 부품 중 우선순위가 가장 높은 부품 선택
    std::string selectedComponent = "No selected";
    if (machinePtr->inventory.count("aaa") > 0) {
        selectedComponent = "aaa";
    } else if (machinePtr->inventory.count("dd") > 0 || machinePtr->inventory.count("cc") > 0 || machinePtr->inventory.count("bb") > 0 || machinePtr->inventory.count("aa") > 0) {
        if (machinePtr->inventory.count("dd") > 0) {
            selectedComponent = "dd";
        } else if (machinePtr->inventory.count("cc") > 0) {
            selectedComponent = "cc";
        } else if (machinePtr->inventory.count("bb") > 0) {
            selectedComponent = "bb";
        } else {
            selectedComponent = "aa";
        }
    } else {
        // 2. 모든 머신은 a, b, c 재료를 무한히 가지고 있다고 가정
        if (machinePtr->inventory.count("a") > 0) {
            selectedComponent = "a";
        } else if (machinePtr->inventory.count("b") > 0) {
            selectedComponent = "b";
        } else if (machinePtr->inventory.count("c") > 0) {
            selectedComponent = "c";
        } else {
            std::cerr << "No available component" << std::endl;
            return;
        }
    }

    // 선택된 부품 출력
    std::cout << "Selected component: " << selectedComponent << std::endl;

    // 선택된 부품을 다음 단계 부품으로 변환
    std::string nextComponent = machinePtr->getOutputForInput(selectedComponent);
    if (!nextComponent.empty()) {
        machinePtr->removeInventory(selectedComponent, 1);
        machinePtr->addInventory(nextComponent, 1);
    }

    // 변환된 부품 출력
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

void Machine::addInventory(const std::string& component, int quantity) {
    inventory[component] += quantity;
}

void Machine::removeInventory(const std::string& component, int quantity) {
    if (inventory.count(component) > 0) {
        inventory[component] -= quantity;
        if (inventory[component] <= 0) {
            inventory.erase(component);
        }
    }
}

int Machine::getInventoryQuantity(const std::string& component) const {
    if (inventory.count(component) > 0) {
        return inventory.at(component);
    }
    return 0;
}