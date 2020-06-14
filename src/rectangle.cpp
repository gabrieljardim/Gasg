#include "rectangle.h"

Rectangle::Rectangle()
  : Rectangle(0, 0, Point2d(0,0))
{

}

Rectangle::Rectangle(int x, int y, int width, int height)
  : Rectangle(width, height, Point2d(x,y))
{

}

Rectangle::Rectangle(int width, int height, Point2d&& position)
  : m_position(position)
  , m_width(width)
  , m_height(height)
{

}

