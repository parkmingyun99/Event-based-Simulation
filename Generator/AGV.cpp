#include "AGV.h"

AGV::AGV(const std::string &AGV_ID, int x, int y)
    : AGV_ID(AGV_ID), x(x), y(y) {}

std::string AGV::getAgvID() const {
    return AGV_ID;
}

int AGV::getX() const {
    return x;
}

int AGV::getY() const {
    return y;
}

void AGV::exportToCSV(const std::string &filename, const std::vector<AGV> &AGV) {
    std::ofstream file(filename);

    file << "AGV_ID,X,Y\n";

    for (const auto &AGV : AGV) {
        file << AGV.getAgvID() << ","
             << AGV.getX() << ","
             << AGV.getY() << "\n";
    }
    file.close();
}
