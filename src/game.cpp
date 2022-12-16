#include <cstdlib>
#include <cwctype>
#include <game.hpp>

char HORIZONTAL_LINE[4]    = "━";
char VERTICAL_LINE[4]      = "┃";
char CORNER_TOPLEFT[4]     = "┏";
char CORNER_TOPRIGHT[4]    = "┓";
char CORNER_BOTTOMRIGHT[4] = "┛";
char CORNER_BOTTOMLEFT[4]  = "┗";
char APPLE[8]              = "🍎";
// The apple emoji is two characters wide
int APPLE_WIDTH = 2;

Point SCORE_POSTION{2, 0};

Game::Game(Point draw_pos, Point size)
  : snake(Snake(Point{5, 3}, Heading::RIGHT, 3)),
  draw_pos(draw_pos), size(size), score(0)
{
  inner_draw_pos = Point{draw_pos.x + 1, draw_pos.y + 1};
  field_size = Point{size.x - 1, size.y - 1};
  move_apple();
}

bool Game::update() {
  return handle_input();
}

bool Game::handle_input() {
  /* Handle user input.
   * 
   * Return false if the game should quit.
   * */
  int ch;
  while ((ch = getch()) != ERR) {
    if (ch == 'q') {
      return false;
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
  ate_apple = false;
  if (snake.update(apple, APPLE_WIDTH)) {
    ate_apple = true;
    score++;
    move_apple();
  }
  if (snake.check_collision(field_size)) {
    return false;
  }
  return true;
}

void Game::move_apple() {
  do {
    apple.x = rand() % (field_size.x - APPLE_WIDTH + 1);
    apple.y = rand() % field_size.y;
  } while (snake.intersects(apple));
}

void Game::draw(WINDOW* win) {
    snake.draw(win, Point{inner_draw_pos.x, inner_draw_pos.y});
    draw_outline(win);
    draw_apple(win);
    draw_score(win);
}

void Game::draw_outline(WINDOW* win) {
    // Draw outline
    for (int x = 1; x <= size.x - 1; x++) {
      mvwprintw(win, draw_pos.y, draw_pos.x + x, "%s", HORIZONTAL_LINE);
      mvwprintw(win, draw_pos.y + size.y, draw_pos.x + x, "%s", HORIZONTAL_LINE);
    }
    for (int y = 1; y <= size.y - 1; y++) {
      mvwprintw(win, draw_pos.y + y, draw_pos.x, "%s", VERTICAL_LINE);
      mvwprintw(win, draw_pos.y + y, draw_pos.x + size.x, "%s", VERTICAL_LINE);
    }
    // Corners
    mvwprintw(win, draw_pos.y, draw_pos.x, "%s", CORNER_TOPLEFT);
    mvwprintw(win, draw_pos.y + size.y, draw_pos.x, "%s", CORNER_BOTTOMLEFT);
    mvwprintw(win, draw_pos.y, draw_pos.x + size.x, "%s", CORNER_TOPRIGHT);
    mvwprintw(win, draw_pos.y + size.y, draw_pos.x + size.x, "%s", CORNER_BOTTOMRIGHT);
}

void Game::draw_apple(WINDOW* win) {
  mvwprintw(win, apple.y + inner_draw_pos.y, apple.x + inner_draw_pos.x, "%s", APPLE);
}

void Game::draw_score(WINDOW* win) {
  mvwprintw(win, SCORE_POSTION.y, SCORE_POSTION.x, " Score: %ld ", score);
}
