#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include <vector>
#include <fstream>
#include "EoModel.h"

class Machine : public EoModel{
private:
    int createdAt; // 머신 생성 시간. 아마 0
    std::string machineName; // 머신 이름. m1같이
    int processTime; // 머신의 소요시간
    int x; // 머신의 위치
    int y; // 머신의 위치
    bool isUse=true; // 머신의 사용 여부
    std::unordered_map<std::string, std::string> inputOutputRule; // 머신의 룰. a가 입력이면, b로 출력한다 등의 룰을 정의하는 자료형.

public:
    Machine();
    Machine(const int createdAt,const std::string& machineName, const int processTime, const int x, const int y);
    virtual ~Machine();

    std::string getMachineName() const;
    int getProcessTime() const;
    bool getIsUse() const; // Getter 메서드 추가
    void setIsUse(bool isUse); // Setter 메서드 추가
    int getCreatedAt() const;
    // static void exportToCSV(const std::string& filename, const std::vector<Machine> machine);

    void handle(void* message) override;
    void initialize() override;

    // 머신에 대한 input-output 규칙 추가
    void addInputOutputRule(const std::string& input, const std::string& output);

    // 입력에 대한 출력 반환
    std::string getOutputForInput(const std::string& input) const;
};

#endif