#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "EoModel.h"
#include "Position.h"

class Machine : public EoModel {
private:
    int createdAt; // 머신 생성 시간. 아마 0
    std::string machineName; // 머신 이름. m1같이
    int processTime; // 머신의 소요시간
    Position position; // 머신의 위치
    bool isUse = true; // 머신의 사용 여부
    std::unordered_map<std::string, std::string> inputOutputRule; // 머신의 룰. a가 입력이면, b로 출력한다 등의 룰을 정의하는 자료형.
    std::unordered_map<std::string, int> inventory; // 머신이 가진 부품의 재고. key: 부품명, value: 개수
    
public:
    Machine();
    Machine(const int createdAt, const std::string& machineName, const int processTime, const Position& position);
    virtual ~Machine();

    std::string getMachineName() const;
    int getProcessTime() const;
    bool getIsUse() const; // Getter 메서드 추가
    void setIsUse(bool isUse); // Setter 메서드 추가
    int getCreatedAt() const;
    Position getPosition() const;
    
    void handle(void* message) override;
    void initialize() override;

    void addInputOutputRule(const std::string& input, const std::string& output);
    std::string getOutputForInput(const std::string& input) const;

    void addInventory(const std::string& component, int quantity);
    void removeInventory(const std::string& component, int quantity);
    int getInventoryQuantity(const std::string& component) const;
};

#endif