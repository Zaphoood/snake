#include <cwctype>
#include <game.hpp>


Game::Game()
  : snake(Snake(Point{10, 10}, Heading::RIGHT, 3))
{
  apple = Point{0, 0};
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
  snake.update(apple);
  return true;
}

void Game::draw(WINDOW* win) {
    mvwprintw(win, 0, 0, "%d", (int) snake.get_heading());
    snake.draw(win);
}
