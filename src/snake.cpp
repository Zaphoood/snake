#include <vector>
#include <iostream>

#include <ncurses.h>

#include <snake.hpp>
#include <color.hpp>

Snake::Snake(Point start, Heading heading, int start_size) {
    head = start;
    this->heading = heading;
    body.push_front(head);
    for (int i = 0; i < start_size; i++) {
      smove(true);
    }
}

bool Snake::update(Point apple, int apple_width) {
  /* Move snake, check self and bounds collision and apple eating
   * Apple width specifies the number of characters that the apple is wide
   * Returns true if apple was eaten
   */
  bool ate = (apple.x <= head.x && head.x <= apple.x + apple_width - 1 && apple.y == head.y);
  smove(ate);
  return ate;
}

void Snake::smove(bool grow) {
  switch (heading) {
    case Heading::RIGHT:
      head.x++;
      break;
    case Heading::DOWN:
      head.y++;
      break;
    case Heading::LEFT:
      head.x--;
      break;
    case Heading::UP:
      head.y--;
      break;
  }
  body.push_front(head);
  if (!grow) {
    body.pop_back();
  }
}

bool Snake::intersects(Point point) {
  for (std::deque<Point>::iterator it = body.begin(); it != body.end(); ++it) {
    if (it->x == point.x && it->y == point.y) {
      return true;
    }
  }
  return false;
}

bool Snake::check_collision(Point boundaries) {
  if (head.x < 0 || head.x >= boundaries.x || head.y < 0 || head.y >= boundaries.y) {
    return true;
  }
  for (std::deque<Point>::iterator it = ++body.begin(); it != body.end(); ++it) {
    if (it->x == head.x && it->y == head.y) {
      return true;
    }
  }
  return false;
}

Heading Snake::get_heading() {
  return heading;
}

void Snake::set_heading(Heading new_heading) {
  // Check that new heading is not opposite of current heading
  if (((int) new_heading + 2) % 4 != (int) heading) {
    heading = new_heading;
  }
}

void Snake::draw(WINDOW* win, Point offset) {
  attron(COLOR_PAIR(COLOR_SNAKE));
  int i = 0;
  for (Point it : body) {
    i++;
    mvwprintw(win, it.y + offset.y, it.x + offset.x, "█");
  }
  attroff(COLOR_PAIR(COLOR_SNAKE));
}

