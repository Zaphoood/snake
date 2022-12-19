#include <array>
#include <vector>
#include <iostream>
#include <map>

#include <ncurses.h>

#include <snake.hpp>
#include <color.hpp>

const char BLOCK_FULL[4] = "█";
const std::array<std::array<std::string, 8>, 2> BLOCKS = {{
  {" ", "▏", "▎", "▍", "▌", "▋", "▊", "▉"},
  {" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇"}
}};
/* Map each heading to an index of the BLOCKS array */
const std::map<Heading, int> HEADING_BLOCK = {
  {Heading::RIGHT, 0},
  {Heading::UP,    1},
  {Heading::LEFT,  0},
  {Heading::DOWN,  1},
};
/* For which headings to invert the last element of the body */
const std::map<Heading, bool> HEADING_INVERT = {
  {Heading::RIGHT, false},
  {Heading::UP,    false},
  {Heading::LEFT,  true},
  {Heading::DOWN,  true},
};


Snake::Snake(Point start, Heading heading, int start_size) {
  init(start, heading, start_size);
}

void Snake::init(Point start, Heading heading, int start_size) {
    head = start;
    this->heading = heading;
    body.clear();
    body.push_front(head);
    for (int i = 0; i < start_size; i++) {
      smove(true);
    }
}

bool Snake::tick(Point fruit) {
  /* Move snake, check self and bounds collision and fruit eating
   * Apple width specifies the number of characters that the fruit is wide
   * Returns true if fruit was eaten
   */
  bool ate = util::intersects_wide_char(head, fruit);
  smove(ate);
  return ate;
}

Point Snake::get_head() {
  return head;
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

bool Snake::intersects_wide_char(Point point) {
  for (std::deque<Point>::iterator it = body.begin(); it != body.end(); ++it) {
    if (util::intersects_wide_char(*it, point)) {
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

void Snake::draw(WINDOW* win, Point offset, int subframe) {
  attron(COLOR_PAIR(COLOR_SNAKE));
  for (std::deque<Point>::iterator it = body.begin(); it != body.end(); it++) {
    mvwprintw(win, it->y + offset.y, it->x + offset.x, "%s", BLOCK_FULL);
  }
  const std::array<std::string, 8> blocks = BLOCKS[HEADING_BLOCK.at(heading)];
  bool invert = HEADING_INVERT.at(heading);
  int block_index;
  switch (heading) {
    case Heading::RIGHT:
    case Heading::UP:
      block_index = std::min(blocks.size() - 1, (size_t) subframe);
      break;
    case Heading::DOWN:
    case Heading::LEFT:
      block_index = std::max((size_t) 0, blocks.size() - subframe - 1);
      break;
  }
  if (invert) {
    attron(COLOR_PAIR(COLOR_SNAKE_INV));
  }
  mvwprintw(win, offset.y + head.y, offset.x + head.x, "%s", blocks[block_index].c_str());
  if (invert) {
    attroff(COLOR_PAIR(COLOR_SNAKE_INV));
  } else {
    attroff(COLOR_PAIR(COLOR_SNAKE));
  }
}

