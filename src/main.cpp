#include <locale.h>
#include <chrono>
#include <thread>
#include <iostream>

#include <ncurses.h>

#include <game.hpp>
#include <color.hpp>

/* Duration of one tick */
int TICK_DELAY_MS = 100;
/* Number of subframes per tick. */
int N_SUBFRAMES = N_BLOCKS;
int SUBFRAME_DELAY_MS = TICK_DELAY_MS / N_SUBFRAMES;
int MAX_WIDTH = 30;
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
  // Set up color
  if (!has_colors()) {
    endwin();
    std::cout << "Your terminal doesn't support color :(\n";
    return 0;
  }
  start_color();
  // Use the terminal's default colors when -1 is specified
  use_default_colors();
  short BACKGROUND = 256 - 22;
  init_pair(COLOR_DEFAULT, COLOR_WHITE, BACKGROUND);
  init_pair(COLOR_SNAKE, COLOR_GREEN, BACKGROUND);
  init_pair(COLOR_SNAKE_INV, BACKGROUND, COLOR_GREEN);
  wbkgd(win, COLOR_PAIR(COLOR_DEFAULT));

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

  // TODO: Remove unused variable
  int ch;
  while (1) {
    if (!game.tick()) {
      break;
    }
    for (int subframe = 0; subframe < N_SUBFRAMES; subframe++) {
      werase(win);
      game.draw(win, subframe);
      wrefresh(win);
      std::this_thread::sleep_for(std::chrono::milliseconds(SUBFRAME_DELAY_MS));
    }
  }

  endwin();
  return 0;
}
