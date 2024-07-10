#include <cmath>
#include <limits>
#include "AGV.h"
#include "Machine.h"
#include "Storage.h"

/*
 * AGV 클래스의 생성자
 * 생성자에서는 아무 작업도 하지 않습니다.
 */
AGV::AGV() {
   setName("AGV");
}

/*
 * 새로운 AGV 추가 메서드
 * AGV 번호, 초기 위치, 속도를 인자로 받아 새로운 AGV를 추가합니다.
 */
void AGV::addAGV(int agvNumber, const Position& position, double speed) {
    agvNumbers.push_back(agvNumber);
    positions.push_back(position);
    carryingComponents.emplace_back();
    totalTravelTimes.push_back(0.0);
    totalTravelDistances.push_back(0.0);
    speeds.push_back(speed);
}

// AGV 정보 getter 메서드
int AGV::getAgvNumber(int index) const {
    return agvNumbers[index];
}

Position AGV::getPosition(int index) const {
    return positions[index];
}

std::queue<std::string> AGV::getCarryingComponents(int index) const {
    return carryingComponents[index];
}

double AGV::getTotalTravelTime(int index) const {
    return totalTravelTimes[index];
}

double AGV::getTotalTravelDistance(int index) const {
    return totalTravelDistances[index];
}

double AGV::getSpeed(int index) const {
    return speeds[index];
}

// AGV 정보 setter 메서드
void AGV::setPosition(int index, const Position& newPosition) {
    positions[index] = newPosition;
}

void AGV::addCarryingComponent(int index, const std::string& component) {
    carryingComponents[index].push(component);
}

void AGV::removeCarryingComponent(int index) {
    if (!carryingComponents[index].empty()) {
        carryingComponents[index].pop();
    }
}

void AGV::updateTravelTime(int index, double time) {
    totalTravelTimes[index] += time;
}

void AGV::updateTravelDistance(int index, double distance) {
    totalTravelDistances[index] += distance;
}

void AGV::setSpeed(int index, double newSpeed) {
    speeds[index] = newSpeed;
}

/*
 * handle 메서드 오버라이드
 * AGV의 동작을 정의합니다.
 */
void AGV::handle(void* message) {
    if (message == nullptr) {
        std::cerr << "Invalid message" << std::endl;
        return;
    }

    Machine* machinePtr = reinterpret_cast<Machine*>(message);

    // 머신의 위치 가져오기
    Position machinePosition = machinePtr->getPosition();

    // 스토리지의 위치 가져오기
    Position storagePosition = Storage::getPosition();

    // AGV에서 스토리지까지의 거리 + 스토리지에서 머신까지의 거리가 가장 짧은 AGV 찾기
    int closestAgvIndex = -1;
    double shortestDistance = std::numeric_limits<double>::max();

    for (int i = 0; i < positions.size(); i++) {
        double agvToStorageDistance = calculateDistance(positions[i], storagePosition);
        double storageToMachineDistance = calculateDistance(storagePosition, machinePosition);
        double totalDistance = agvToStorageDistance + storageToMachineDistance;

        if (totalDistance < shortestDistance) {
            shortestDistance = totalDistance;
            closestAgvIndex = i;
        }
    }

    // 가장 가까운 AGV 선택 및 위치 변경
    if (closestAgvIndex != -1) {
        std::cout << "Closest AGV to machine " << machinePtr->getMachineName() << " is AGV " << agvNumbers[closestAgvIndex]
                  << " at position (" << positions[closestAgvIndex].getX() << ", " << positions[closestAgvIndex].getY() << ")" << std::endl;

        // AGV에서 스토리지까지의 거리와 스토리지에서 머신까지의 거리 계산
        int agvToStorageDistance = calculateDistance(positions[closestAgvIndex], storagePosition);
        int storageToMachineDistance = calculateDistance(storagePosition, machinePosition);

        // AGV의 위치를 머신의 위치로 변경
        positions[closestAgvIndex] = machinePosition;
        std::cout << "AGV " << agvNumbers[closestAgvIndex] << " moved to (" << positions[closestAgvIndex].getX() << ", " << positions[closestAgvIndex].getY() << ")" << std::endl;
      
        // totalTravelDistances 업데이트
        totalTravelDistances[closestAgvIndex] += agvToStorageDistance + storageToMachineDistance;
        machinePtr->addInventory("a",1);
        machinePtr->addInventory("b",1);
        machinePtr->addInventory("c",1);
        schedule(totalTravelDistances[closestAgvIndex], "Machine" , machinePtr);

        // 지금까지 이동한 총 거리 출력
        std::cout << "AGV " << agvNumbers[closestAgvIndex] << " has traveled a total distance of " << totalTravelDistances[closestAgvIndex] << std::endl;
   
    } else {
        std::cerr << "No AGV found" << std::endl;
    }
}

double AGV::calculateDistance(const Position& p1, const Position& p2) {
    double dx = std::abs(static_cast<double>(p1.getX() - p2.getX()));
    double dy = std::abs(static_cast<double>(p1.getY() - p2.getY()));
    return dx + dy;
} // 맨허튼 거리 계산기.

/*
 * initialize 메서드 오버라이드
 * AGV 초기화 작업을 수행합니다.
 */
void AGV::initialize() {
    addAGV(1, Position(1, 1), 1.0); // AGV 1 생성, 위치: (1, 2), 속도: 1.0
   //  addAGV(2, Position(1, 3), 1.0); // AGV 2 생성, 위치: (1, 3), 속도: 1.0
   //  addAGV(3, Position(1, 4), 1.0); // AGV 3 생성, 위치: (1, 4), 속도: 1.0
   //  addAGV(4, Position(1, 5), 1.0); // AGV 4 생성, 위치: (1, 5), 속도: 1.0
   //  addAGV(5, Position(1, 6), 1.0); // AGV 5 생성, 위치: (1, 6), 속도: 1.0
   //  addAGV(6, Position(1, 7), 1.0); // AGV 6 생성, 위치: (1, 7), 속도: 1.0
}