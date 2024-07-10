#include "Machine.h"

Machine::Machine(const std::string& MACHINE_ID, const std::string& GROUP, int MAX_QUEUE)
: MACHINE_ID(MACHINE_ID), GROUP(GROUP), MAX_QUEUE(MAX_QUEUE) {}

std::string Machine::getMachineID() const {
    return MACHINE_ID;
}

std::string Machine::getGroup() const {
    return GROUP;
}

int Machine::getMaxQueue() const {
    return MAX_QUEUE;
}

void Machine::exportToCSV(const std::string &filename, const std::vector <Machine>& machines) {
    std::ofstream file(filename);

    file << "MACHINE_ID,GROUP,MAX_QUEUE\n";

    for(const auto& Machine:machines) {
        file << Machine.getMachineID() << ","
             << Machine.getGroup() << ","
             << Machine.getMaxQueue() << "\n";
    }

    file.close();
}
