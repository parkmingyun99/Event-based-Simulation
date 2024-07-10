#include "Map.h"

// Constructor to create an NxM map
Map::Map(int rows, int cols) : rows_(rows), cols_(cols), map_(rows, std::vector<int>(cols, 0)) {}

// Function to display the map
void Map::Display() const {
    for (const auto& row : map_) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

// Set method implementation
void Map::Set(int x, int y, int value) {
    // Check if the given coordinates are within the bounds of the map
    if (x >= 0 && x < rows_ && y >= 0 && y < cols_) {
        // Set the value at the specified position
        map_[x][y] = value;
    } else {
        // Display an error message if the coordinates are out of bounds
        std::cerr << "Error: Coordinates out of bounds!" << std::endl;
    }
}

// Get method implementation
int Map::Get(int x, int y) const {
    // Check if the given coordinates are within the bounds of the map
    if (x >= 0 && x < rows_ && y >= 0 && y < cols_) {
        // Return the value at the specified position
        return map_[x][y];
    } else {
        // Display an error message if the coordinates are out of bounds
        std::cerr << "Error: Coordinates out of bounds!" << std::endl;
        // Return a default value indicating an error
        return -1;
    }
}


