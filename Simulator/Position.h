#pragma once
#ifndef POSITION_H
#define POSITION_H

#include <fstream>
#include <random>

class Position {
  private:
    int y;
    int x;

  public:
    Position();
    Position(const int _y, const int _x);

    bool operator ==(const Position &temp) const;
    bool operator!=(const Position &temp) const;
    friend std::ostream &operator<<(std::ostream &out, const Position &pos);

    int getY() const;
    int getX() const;
    void increase_y();
    void increase_x();
    void decrease_y();
    void decrease_x();
    static Position position_null();
};

#endif