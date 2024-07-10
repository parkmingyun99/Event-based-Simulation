#include "Process_rule.h"

Process_rule::Process_rule(const std::string& PROCESS_NAME, int STEP, const std::string& GROUP, const std::string& MACHINE_ID, int PROCESS_TIME)
: PROCESS_NAME(PROCESS_NAME), STEP(STEP), GROUP(GROUP), MACHINE_ID(MACHINE_ID), PROCESS_TIME(PROCESS_TIME) {}

std::string Process_rule::getProcessName() const {
    return PROCESS_NAME;
}

int Process_rule::getStep() const {
    return STEP;
}

std::string Process_rule::getGroup() const {
    return GROUP;
}

std::string Process_rule::getMachineID() const {
    return MACHINE_ID;
}

int Process_rule::getProcessTime() const {
    return PROCESS_TIME;
}

void Process_rule::exportToCSV(const std::string &filename, const std::vector <Process_rule> &Process_rules) {
    std::ofstream file(filename);

    file << "PROCESS_NAME, STEP, GROUP, MACHINE_ID, PROCESS_TIME\n";

    for(const auto& Process_rule:Process_rules) {
        //MACHINE_ID를 하나의 셀로 저장하기 위한 코드(,로 구분되어 셀 증가 문제 해결)
        std::string MACHINE_ID = Process_rule.getMachineID();
        if (MACHINE_ID.find(',') != std::string::npos) {
            MACHINE_ID = "\"" + MACHINE_ID + "\"";
        }

        file << Process_rule.getProcessName() << ","
             << Process_rule.getStep() << ","
             << Process_rule.getGroup() << ","
             << MACHINE_ID << ','
             << Process_rule.getProcessTime() << '\n';
    }
    file.close();
}
