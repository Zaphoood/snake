#include <ncurses.h>

#include <snake.hpp>

class Game {
  private:
    Snake snake;
    Point apple;

    Point draw_pos;
    Point size;
    Point inner_draw_pos;
    Point field_size;

    bool running = false;
    bool handle_input();
    void draw_outline(WINDOW* win);
    void draw_apple(WINDOW* win);
    void move_apple();

    bool ate_apple = false;
  public:
    Game(Point draw_pos, Point size);

    bool update();
    void draw(WINDOW* win);
};
