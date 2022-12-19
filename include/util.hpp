#pragma once

struct Point {
  int x;
  int y;
  bool operator==(Point other) {
    return x == other.x && y == other.y;
  }
  Point operator+(Point other) {
    return Point{x + other.x, y + other.y};
  }
  Point operator-(Point other) {
    return Point{x - other.x, y - other.y};
  }
};

namespace util {
  bool intersects_wide_char(Point p, Point wide_char);
}
