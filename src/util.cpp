#include <util.hpp>

namespace util {
  bool intersects_wide_char(Point p, Point wch) {
    /* Check if a given point intersects with a given wide unicode character
     */
    return p == wch || (p.x == wch.x + 1 && p.y == wch.y);
  }
}
