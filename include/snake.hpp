#include <cstdint>
#include <deque>

#include <ncurses.h>

struct Point {
  int x;
  int y;
};

enum class Heading {
  RIGHT = 0,
  UP = 1,
  LEFT,
  DOWN,
};

class Snake {
  private:
    std::deque<Point> body;
    Point head;
    Heading heading; // Direction the snake is going in

    // Weird naming so that we don't shadow ncurses's `move`
    void smove(bool grow);

  public:
    Snake(Point start, Heading heading, int start_size);

    bool update(Point apple);
    Heading get_heading();
    void set_heading(Heading heading);
    void draw(WINDOW* win);
};
