#include <cstdint>
#include <deque>

#include <ncurses.h>

struct Point {
  int x;
  int y;
  bool operator==(Point other) {
    return x == other.x && y == other.y;
  }
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
    // Direction the snake is going in
    Heading heading;

    // Weird naming so that we don't shadow ncurses's `move`
    void smove(bool grow);

  public:
    Point head;
    Snake(Point start, Heading heading, int start_size);

    bool update(Point apple, int apple_width);
    bool check_collision(Point boundaries);
    Heading get_heading();
    void set_heading(Heading heading);
    void draw(WINDOW* win, Point offset);
};
