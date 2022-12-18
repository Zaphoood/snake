#include <cstdlib>
#include <cwctype>

#include <game.hpp>
#include <color.hpp>

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
int SNAKE_START_SIZE = 3;

Game::Game(Point draw_pos, Point size)
  : snake(Point{0, 0}, Heading::RIGHT, 0),
  draw_pos(draw_pos), size(size), score(0)
{
  inner_draw_pos = Point{draw_pos.x + 1, draw_pos.y + 1};
  field_size = Point{size.x - 2, size.y - 2};
  snake.init(Point{field_size.x / 2 - SNAKE_START_SIZE, field_size.y / 2}, Heading::RIGHT, SNAKE_START_SIZE);
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
  steered_this_frame = false;
  // Handle queued input from previous frame, if there is any
  if (input_queue != -1) {
    handle_steering(input_queue);
    input_queue = -1;
    steered_this_frame = true;
  }
  while ((ch = getch()) != ERR) {
    if (ch == 'q') {
      return false;
    }
    if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
      if (!steered_this_frame) {
        handle_steering(ch);
        steered_this_frame = true;
      } else if (input_queue == -1) {
          input_queue = ch;
      }
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
void Game::handle_steering(int ch) {
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

void Game::move_apple() {
  do {
    apple.x = rand() % (field_size.x - APPLE_WIDTH + 1);
    apple.y = rand() % field_size.y;
  } while (snake.intersects_wide_char(apple));
}

void Game::draw(WINDOW* win) {
  snake.draw(win, inner_draw_pos);
  attron(COLOR_PAIR(COLOR_DEFAULT));
  draw_outline(win);
  draw_apple(win);
  draw_score(win);
  attroff(COLOR_PAIR(COLOR_DEFAULT));
}

void Game::draw_outline(WINDOW* win) {
    // Draw outline
    for (int x = 1; x <= size.x - 2; x++) {
      mvwprintw(win, draw_pos.y, draw_pos.x + x, "%s", HORIZONTAL_LINE);
      mvwprintw(win, draw_pos.y + size.y - 1, draw_pos.x + x, "%s", HORIZONTAL_LINE);
    }
    for (int y = 1; y <= size.y - 2; y++) {
      mvwprintw(win, draw_pos.y + y, draw_pos.x, "%s", VERTICAL_LINE);
      mvwprintw(win, draw_pos.y + y, draw_pos.x + size.x - 1, "%s", VERTICAL_LINE);
    }
    // Corners
    mvwprintw(win, draw_pos.y,              draw_pos.x, "%s", CORNER_TOPLEFT);
    mvwprintw(win, draw_pos.y + size.y - 1, draw_pos.x, "%s", CORNER_BOTTOMLEFT);
    mvwprintw(win, draw_pos.y,              draw_pos.x + size.x - 1, "%s", CORNER_TOPRIGHT);
    mvwprintw(win, draw_pos.y + size.y - 1, draw_pos.x + size.x - 1, "%s", CORNER_BOTTOMRIGHT);
}

void Game::draw_apple(WINDOW* win) {
  mvwprintw(win, apple.y + inner_draw_pos.y, apple.x + inner_draw_pos.x, "%s", APPLE);
}

void Game::draw_score(WINDOW* win) {
  mvwprintw(win, draw_pos.y + SCORE_POSTION.y, draw_pos.x + SCORE_POSTION.x, " Score: %ld ", score);
}
