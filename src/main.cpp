#include <locale.h>
#include <chrono>
#include <thread>
#include <iostream>

#include <ncurses.h>

#include <snake.hpp>

int FRAME_DELAY_MS = 100;

int main(int argc, char ** argv)
{
  setlocale(LC_ALL, "");
  
  Snake snake = Snake(Point{10, 10}, Heading::RIGHT, 3);

  WINDOW* win = initscr();
  raw();
  // Don't wait for user input
  nodelay(win, TRUE);
  // Don't echo user input
  noecho();
  // Enable arrow keys etc.
  keypad(stdscr, TRUE);
  // Hide cursor
  curs_set(0);

  Point apple = {0, 0};
  int i = 0;
  int ch;
  bool running = true;
  while (running) {
    // Handle input
    while ((ch = getch()) != ERR) {
      if (ch == 'q') {
        running = false;
        break;
      }
      switch (ch) {
        case 'w':
          snake.set_heading(Heading::UP);
          break;
        case 'a':
          snake.set_heading(Heading::LEFT);
          break;
        case 's':
          snake.set_heading(Heading::DOWN);
          break;
        case 'd':
          snake.set_heading(Heading::RIGHT);
          break;
      }
    }
    werase(win);
    mvprintw(0, 0, "%d", (int) snake.get_heading());
    snake.draw();
    snake.update(apple);

    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY_MS));
  }

  endwin();
  return 0;
}
