#include "Cell.h"

// Constructor
Cell::Cell(int cell_type, int type_count, int x, int y)
    : cell_type_(cell_type), type_count_(type_count), x_(x), y_(y) {}



int Cell::GetCellType() const {
    return cell_type_;
}

int Cell::GetTypeCount() const {
    return type_count_;
}

int Cell::GetX() const {
    return x_;
}

int Cell::GetY() const {
    return y_;
}

// Export cell data to a CSV file
void Cell::exportToCSV(const std::string &filename, const std::vector<Cell> &cells) {
    std::ofstream file(filename);

    file << "CELL_TYPE,TYPE_COUNT,X,Y\n";

    for(const auto& cell : cells) {
        file << cell.GetCellType() << ","
             << cell.GetTypeCount() << ","
             << cell.GetX() << ","
             << cell.GetY() << "\n";
    }
    file.close();
}


// Comparison function for qsort
int Cell::compareCells(const void* a, const void* b) {
    Cell* cellA = (Cell*)a;
    Cell* cellB = (Cell*)b;

    if (cellA->GetCellType() == cellB->GetCellType()) {
        return cellA->GetTypeCount() - cellB->GetTypeCount();
    }
    return cellA->GetCellType() - cellB->GetCellType();
}