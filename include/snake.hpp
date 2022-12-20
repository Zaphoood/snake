#pragma once

#include <array>
#include <map>
#include <string>
#include <deque>

#include <ncurses.h>

#include <util.hpp>

enum class Heading {
  RIGHT = 0,
  UP    = 1,
  LEFT  = 2,
  DOWN  = 3,
};

const char BLOCK_FULL[4] = "█";
const int N_BLOCKS = 8;
const std::array<std::array<std::string, N_BLOCKS>, 2> BLOCKS = {{
  {" ", "▏", "▎", "▍", "▌", "▋", "▊", "▉"},
  {" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇"}
}};
/* Map each heading to an index of the BLOCKS array */
const std::map<Heading, int> HEADING_BLOCK = {
  {Heading::RIGHT, 0},
  {Heading::UP,    1},
  {Heading::LEFT,  0},
  {Heading::DOWN,  1},
};

/* For which headings to invert the last element of the body */
const std::map<Heading, bool> HEADING_INVERT = {
  {Heading::RIGHT, false},
  {Heading::UP,    false},
  {Heading::LEFT,  true},
  {Heading::DOWN,  true},
};
class Snake {
  private:
    std::deque<Point> body;
    /* Direction the snake is going in */
    Heading heading;
    Point head;
    Point old_tail;

    // Weird naming so that we don't shadow ncurses's `move`
    void smove(bool grow);

    void draw_fractional_block(WINDOW* win, Point position, Heading direction, int frac);

  public:
    Snake(Point start, Heading heading, int start_size);
    void init(Point start, Heading heading, int start_size);

    bool tick(Point fruit);
    Point get_head();
    bool check_collision(Point boundaries);
    bool intersects_wide_char(Point p);
    Heading get_heading();
    void set_heading(Heading heading);
    void draw(WINDOW* win, Point offset, int subframe);
};
