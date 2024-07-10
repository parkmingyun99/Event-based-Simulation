#pragma once
#include <vector>
#include <iostream>

class Map {
public:
    // Constructor to create an NxM map
    Map(int rows, int cols);

    // Function to display the map
    void Display() const;

    // Set method to set value at a specific position
    void Set(int x, int y, int value);
    // Get method to retrieve value at a specific position
    int Get(int x, int y) const;
    

private:
    int rows_;
    int cols_;
    std::vector<std::vector<int>> map_;
};
