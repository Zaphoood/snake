#pragma once

#include <ncurses.h>

#include <snake.hpp>
#include <string>

class Game {
  private:
    // Queue at most one input for the next frame
    int input_queue = -1;
    bool steered_this_frame;
    Snake snake;
    Point fruit;
    int fruit_index;
    std::string fruit_str;

    Point draw_pos;
    Point size;
    Point inner_draw_pos;
    Point field_size;

    bool running = false;
    bool handle_input();
    void handle_steering(int ch);
    void draw_outline(WINDOW* win);
    void draw_fruit(WINDOW* win);
    void draw_score(WINDOW* win);
    void move_fruit();

    bool ate_fruit = false;
    long score = 0;

  public:
    Game(Point draw_pos, Point size);

    bool update();
    void draw(WINDOW* win);
};
