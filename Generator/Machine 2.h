#include <string>
#include <vector>
#include <fstream>

class Machine {
private:
    std::string MACHINE_ID;
    std::string GROUP;
    int MAX_QUEUE;

public:
    Machine(const std::string& MACHINE_ID, const std::string& GROUP, int MAX_QUEUE);

    std::string getMachineID() const;
    std::string getGroup() const;
    int getMaxQueue() const;

    static void exportToCSV(const std::string& filename, const std::vector<Machine>& machines);
};