#pragma once
#include <fstream>
#include <string>
#include <vector>

class Cell {
public:
    Cell(int cell_type, int type_count_, int x, int y);

    // Getter methods
    int GetCellType() const;
    int GetTypeCount() const;
    int GetX() const;
    int GetY() const;

    // Export cell data to a CSV file
    static void exportToCSV(const std::string &filename, const std::vector<Cell> &cells);

    // Comparison function for qsort
    static int compareCells(const void* a, const void* b);


private:
    int cell_type_;
    int type_count_;
    int x_;
    int y_;
};
