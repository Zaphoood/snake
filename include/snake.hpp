#pragma once

#include <cstdint>
#include <deque>

#include <ncurses.h>

#include <util.hpp>

enum class Heading {
  RIGHT = 0,
  UP = 1,
  LEFT,
  DOWN,
};

class Snake {
  private:
    std::deque<Point> body;
    // Direction the snake is going in
    Heading heading;
    Point head;

    // Weird naming so that we don't shadow ncurses's `move`
    void smove(bool grow);

  public:
    Snake(Point start, Heading heading, int start_size);
    void init(Point start, Heading heading, int start_size);

    bool update(Point fruit);
    Point get_head();
    bool check_collision(Point boundaries);
    bool intersects_wide_char(Point p);
    Heading get_heading();
    void set_heading(Heading heading);
    void draw(WINDOW* win, Point offset);
};
