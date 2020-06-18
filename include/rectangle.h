#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"

class Rectangle
{
public:
  Rectangle();
  Rectangle(int width, int height, int x = 0, int y = 0);
  Rectangle(int width, int height, Point2d&& position = Point2d(0,0));

  inline int width() const {
    return m_width;
  }
  inline int height() const {
    return m_height;
  }

  inline const Point2d& position() const {
    return m_position;
  }

private:
  Point2d m_position;
  int m_width;
  int m_height;

};

#endif // RECTANGLE_H
