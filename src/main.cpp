#include <locale.h>
#include <chrono>
#include <thread>
#include <iostream>

#include <ncurses.h>

#include <game.hpp>

int FRAME_DELAY_MS = 100;
int MAX_WIDTH = 25;
int MAX_HEIGHT = 15;

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
  int actual_width = getmaxx(win);
  int actual_height = getmaxy(win);
  // Center playfield on screen in case screen is to wide/tall
  if (actual_width > MAX_WIDTH) {
    size.x = MAX_WIDTH;
    pos.x = (actual_width - MAX_WIDTH) / 2;
  } else {
    size.x = actual_width;
  }
  if (actual_height > MAX_HEIGHT) {
    size.y = MAX_HEIGHT;
    pos.y = (actual_height - MAX_HEIGHT) / 2;
  } else {
    size.y = actual_height;
  }

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
