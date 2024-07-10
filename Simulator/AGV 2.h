#ifndef AGV_H
#define AGV_H

#include <vector>
#include <queue>
#include <string>
#include "EoModel.h"
#include "Position.h"

/*
 * AGV 클래스
 * 모든 AGV를 관리하는 클래스입니다.
 * 각 AGV의 번호, 위치, 운반 중인 부품 큐, 이동 시간, 이동 거리, 속도를 관리합니다.
 */
class AGV : public EoModel {
private:
    std::vector<int> agvNumbers;        // AGV 번호 저장 벡터
    std::vector<Position> positions;    // AGV 위치 저장 벡터
    std::vector<std::queue<std::string>> carryingComponents; // AGV가 운반 중인 부품 큐 저장 벡터
    std::vector<double> totalTravelTimes; // AGV의 총 이동 시간 저장 벡터
    std::vector<double> totalTravelDistances; // AGV의 총 이동 거리 저장 벡터
    std::vector<double> speeds;         // AGV의 속도 저장 벡터

public:
    AGV();

    // 새로운 AGV 추가
    void addAGV(int agvNumber, const Position& position, double speed);

    // AGV 정보 getter 메서드
    int getAgvNumber(int index) const;
    Position getPosition(int index) const;
    std::queue<std::string> getCarryingComponents(int index) const;
    double getTotalTravelTime(int index) const;
    double getTotalTravelDistance(int index) const;
    double getSpeed(int index) const;

    // AGV 정보 setter 메서드
    void setPosition(int index, const Position& newPosition);
    void addCarryingComponent(int index, const std::string& component);
    void removeCarryingComponent(int index);
    void updateTravelTime(int index, double time);
    void updateTravelDistance(int index, double distance);
    void setSpeed(int index, double newSpeed);

    // EoModel 인터페이스 메서드 오버라이드
    void handle(void* message) override;
    void initialize() override;

    // 두 점 사이의 거리 계산 함수
    static double calculateDistance(const Position& p1, const Position& p2);
};

#endif