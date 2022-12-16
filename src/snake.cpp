#include <vector>
#include <iostream>

#include <ncurses.h>

#include <snake.hpp>

Snake::Snake(Point start, Heading heading, int start_size) {
    head = start;
    this->heading = heading;
    body.push_front(head);
    for (int i = 0; i < 3; i++) {
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

void Snake::set_heading(Heading new_heading) {
  return;
  if (((int) new_heading + 2) % 4 != (int) heading) {
    heading = new_heading;
  }
}

void Snake::draw() {
  int i = 0;
  for (Point it : body) {
    i++;
    mvprintw(it.y, it.x, "█");
  }
}

