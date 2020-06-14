#ifndef POINT_H
#define POINT_H

class Point2d
{
public:
  Point2d();
  Point2d(int x, int y);
  inline const int& x() const {
    return m_x;
  }
  inline const int& y() const {
    return m_y;
  }
private:
  int m_x;
  int m_y;
};

#endif // POINT_H
