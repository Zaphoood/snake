#include <locale.h>
#include <chrono>
#include <thread>
#include <iostream>

#include <ncurses.h>

#include <game.hpp>

int FRAME_DELAY_MS = 100;

int main(int argc, char ** argv)
{
  setlocale(LC_ALL, "");
  srand((unsigned) time(NULL));
  
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

  Point pos{0, 0};
  Point size;
  size.x = getmaxx(win) - 1;
  size.y = getmaxy(win) - 1;

  Game game(pos, size);

  int ch;
  while (1) {
    if (!game.update()) {
      break;
    }
    werase(win);
    game.draw(win);
    wrefresh(win);
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY_MS));
  }

  endwin();
  return 0;
}
