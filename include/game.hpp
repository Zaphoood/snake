#include <ncurses.h>

#include <snake.hpp>

class Game {
  private:
    Snake snake;
    Point apple;

    Point draw_pos;
    Point size;

    bool running = false;
    bool handle_input();
    void draw_outline(WINDOW* win);
    void draw_apple(WINDOW* win);

  public:
    Game(Point draw_pos, Point size);

    bool update();
    void draw(WINDOW* win);
};
