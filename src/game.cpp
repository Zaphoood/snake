#include <array>
#include <cstdlib>
#include <cwctype>

#include <game.hpp>
#include <color.hpp>

const char HORIZONTAL_LINE[4]    = "━";
const char VERTICAL_LINE[4]      = "┃";
const char CORNER_TOPLEFT[4]     = "┏";
const char CORNER_TOPRIGHT[4]    = "┓";
const char CORNER_BOTTOMRIGHT[4] = "┛";
const char CORNER_BOTTOMLEFT[4]  = "┗";
const std::array<std::string, 4> FRUITS = {
  "🎄", "🍪", "🍭", "🎁",
};
const std::string GAME_OVER = "Game Over!";

const Point SCORE_POSTION{2, 0};
const int SNAKE_START_SIZE = 3;

Game::Game(Point draw_pos, Point size)
  : snake(Point{0, 0}, Heading::RIGHT, 0),
  draw_pos(draw_pos), size(size), score(0)
{
  inner_draw_pos = draw_pos + Point{1, 1};
  field_size = size - Point{2, 2};
  reset();
}

/* Update the game's state.
 *
 * Return false if the game was quit.
 */
bool Game::tick() {
  if (!handle_input()) {
    return false;
  }
  if (game_over) {
    return true;
  }
  ate_fruit = false;
  if (snake.tick(fruit)) {
    ate_fruit = true;
    score++;
    move_fruit();
  }
  if (snake.check_collision(field_size)) {
    game_over = true;
  }
  return true;
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
    if (game_over) {
      reset();
      return true;
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

void Game::reset() {
  game_over = false;
  score = 0;
  snake.init(Point{field_size.x / 2 - SNAKE_START_SIZE, field_size.y / 2}, Heading::RIGHT, SNAKE_START_SIZE);
  move_fruit();
}

void Game::move_fruit() {
  // Move fruit
  do {
    fruit.x = rand() % (field_size.x - 1); // -1 because fruits are emojis and therefore wide chars
    fruit.y = rand() % field_size.y;
  } while (snake.intersects_wide_char(fruit));
  // TODO: Select new fruit
  fruit_str = FRUITS[random() % FRUITS.size()];
}

void Game::draw(WINDOW* win, int subframe) {
  snake.draw(win, inner_draw_pos, game_over ? 0 : subframe);
  attron(COLOR_PAIR(COLOR_DEFAULT));
  box(win, draw_pos, size);
  draw_fruit(win);
  draw_score(win);
  if (game_over) {
    draw_game_over(win);
  }
  attroff(COLOR_PAIR(COLOR_DEFAULT));
}

void Game::box(WINDOW* win, Point position, Point size) {
    for (int x = 1; x <= size.x - 2; x++) {
      mvwprintw(win, position.y, position.x + x, "%s", HORIZONTAL_LINE);
      mvwprintw(win, position.y + size.y - 1, position.x + x, "%s", HORIZONTAL_LINE);
    }
    for (int y = 1; y <= size.y - 2; y++) {
      mvwprintw(win, position.y + y, position.x, "%s", VERTICAL_LINE);
      mvwprintw(win, position.y + y, position.x + size.x - 1, "%s", VERTICAL_LINE);
    }
    // Corners
    mvwprintw(win, position.y,              position.x, "%s", CORNER_TOPLEFT);
    mvwprintw(win, position.y + size.y - 1, position.x, "%s", CORNER_BOTTOMLEFT);
    mvwprintw(win, position.y,              position.x + size.x - 1, "%s", CORNER_TOPRIGHT);
    mvwprintw(win, position.y + size.y - 1, position.x + size.x - 1, "%s", CORNER_BOTTOMRIGHT);
}
void Game::fill_box(WINDOW* win, Point position, Point size, char ch) {
  for (int x = position.x; x < position.x + size.x; x++) {
    for (int y = position.y; y < position.y + size.y; y++) {
      mvwprintw(win, y, x, "%c", ch);
    }
  }
}

void Game::draw_fruit(WINDOW* win) {
  mvwprintw(win, fruit.y + inner_draw_pos.y, fruit.x + inner_draw_pos.x, "%s", fruit_str.c_str());
}

void Game::draw_score(WINDOW* win) {
  mvwprintw(win, draw_pos.y + SCORE_POSTION.y, draw_pos.x + SCORE_POSTION.x, " Score: %ld ", score);
}

void Game::draw_game_over(WINDOW* win) {
  Point text_pos{
      draw_pos.x + (size.x - (int) GAME_OVER.size()) / 2,
      draw_pos.y + size.y / 2};
  Point box_pos{text_pos.x - 2, text_pos.y - 1};
  Point box_size{(int) GAME_OVER.size() + 4, 3};
  fill_box(win, box_pos, box_size, ' ');
  box(win, box_pos, box_size);
  mvwprintw(win, text_pos.y, text_pos.x, "%s", GAME_OVER.c_str());
}
