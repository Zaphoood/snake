#include <ncurses.h>

#include <snake.hpp>

class Game {
  private:
    Snake snake;
    Point apple;

    bool running = false;
    bool handle_input();

  public:
    Game();

    bool update();
    void draw(WINDOW* win);
};
