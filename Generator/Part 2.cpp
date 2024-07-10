#include "Part.h"

// Constructor
Part::Part(int partid, const std::vector<int>& processtime, const std::vector<int>& processline)
    : partid_(partid), processtime_(processtime), processline_(processline) {}

// Getter methods
int Part::GetPartId() const {
    return partid_;
}

const std::vector<int>& Part::GetProcessTime() const {
    return processtime_;
}

const std::vector<int>& Part::GetProcessLine() const {
    return processline_;
}

// Setter methods
void Part::SetPartId(int partid) {
    partid_ = partid;
}

void Part::SetProcessTime(const std::vector<int>& processtime) {
    processtime_ = processtime;
}

void Part::SetProcessLine(const std::vector<int>& processline) {
    processline_ = processline;
}

// Export part data to a CSV file
void Part::exportToCSV(const std::string &filename, const std::vector<Part> &parts) {
    std::ofstream file(filename);

    file << "PART_ID,PROCESS_TIME,PROCESS_LINE\n";

    for(const auto& part : parts) {
        file << part.GetPartId() << ",";

        // Write PROCESS_TIME
        for(auto it = part.GetProcessTime().begin(); it != part.GetProcessTime().end(); ++it) {
            file << *it;
            if (std::next(it) != part.GetProcessTime().end()) {
                file << ";"; // Separate process times with a semicolon
            }
        }

        file << ",";

        // Write PROCESS_LINE
        for(auto it = part.GetProcessLine().begin(); it != part.GetProcessLine().end(); ++it) {
            file << *it;
            if (std::next(it) != part.GetProcessLine().end()) {
                file << ";"; // Separate process lines with a semicolon
            }
        }

        file << "\n";
    }
    file.close();
}
