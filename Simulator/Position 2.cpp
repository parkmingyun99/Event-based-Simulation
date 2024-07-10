
#include "Position.h"

Position::Position()
    : y(0), x(0) {
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::normal_distribution<double> distrib(0, 10);
}

Position::Position(const int _y, const int _x)
    : y(_y), x(_x) {
}

bool Position::operator==(const Position &temp) const {
    return (y == temp.y) && (x == temp.x);
}

bool Position::operator!=(const Position &temp) const {
    return !(*this == temp);
}

std::ostream &operator<<(std::ostream &os, const Position &pos) {
    os << "y-Coordinates : " << pos.y << " , x-Coordinates : " << pos.x << "\n";
    return os;
}

int Position::getY() const {
    return y;
}

int Position::getX() const {
    return x;
}

void Position::increase_y() {
    y++;
    return;
}

void Position::increase_x() {
    x++;
    return;
}

void Position::decrease_y() {
    y--;
    return;
}

void Position::decrease_x() {
    x--;
    return;
}

Position Position::position_null() {
    return Position(-1, -1);
}