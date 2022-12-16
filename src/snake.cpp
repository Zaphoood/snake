#include <vector>
#include <iostream>

#include <ncurses.h>

#include <snake.hpp>

Snake::Snake(Point start, Heading heading, int start_size) {
    head = start;
    this->heading = heading;
    body.push_front(head);
    for (int i = 0; i < start_size; i++) {
      smove(true);
    }
}

bool Snake::update(Point apple) {
  // TODO: Check if apple was eaten, if yes, return true
  smove(false);
  return false;
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

bool Snake::check_collision(int left, int right, int top, int bottom) {
  if (head.x < left || head.x >= right || head.y < top || head.y >= bottom) {
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
  if (((int) new_heading + 2) % 4 != (int) heading) {
    heading = new_heading;
  }
}

void Snake::draw(WINDOW* win) {
  int i = 0;
  for (Point it : body) {
    i++;
    mvwprintw(win, it.y, it.x, "█");
  }
}

