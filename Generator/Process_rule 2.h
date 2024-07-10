#include <string>
#include <vector>
#include <fstream>

class Process_rule {
private:
    //공정 이름
    std::string PROCESS_NAME;
    //각 공정의 단계
    int STEP;
    //공정별 처리할 수 있는 머신 그룹
    std::string GROUP;
    //머신 이름
    std::string MACHINE_ID;
    //머신별(그룹별) 공정 처리 시간
    int PROCESS_TIME;

public:
    Process_rule(const std::string& PROCESS_NAME, int STEP, const std::string& GROUP, const std::string& MACHINE_ID, int PROCESS_TIME);

    std::string getProcessName() const;
    int getStep() const;
    std::string getGroup() const;
    std::string getMachineID() const;
    int getProcessTime() const;

    static void exportToCSV(const std::string& filename, const std::vector<Process_rule>& Process_rules);

};
