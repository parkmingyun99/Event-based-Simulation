#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <list>

class Part {
public:
    // Constructor
    Part(int partid, const std::vector<int>& processtime, const std::vector<int>& processline);

    // Getter methods
    int GetPartId() const;
    const std::vector<int>& GetProcessTime() const;
    const std::vector<int>& GetProcessLine() const;

    // Setter methods
    void SetPartId(int partid);
    void SetProcessTime(const std::vector<int>& processtime);
    void SetProcessLine(const std::vector<int>& processline);

    // Export part data to a CSV file
    static void exportToCSV(const std::string &filename, const std::vector<Part> &parts);

private:
    int partid_;
    std::vector<int> processtime_;
    std::vector<int> processline_;
};
