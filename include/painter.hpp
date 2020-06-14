#ifndef PAINTER_HPP
#define PAINTER_HPP

#include "rectangle.h"
#include "color.hpp"

//template<std::size_t width, std::size_t height, ColorType colorType>
template <ColorType colorType>
class Painter {
public:
  template <typename Surface>
  void drawRectangleFill(Surface& surface, const Rectangle& rect, Color<colorType> color, int radius = 0) {
    if((rect.width() + rect.position().x() > surface.getWidth() || (rect.height() + rect.position().y() > surface.getHeight()))) {
      return;
    }

    for(int i = rect.position().x(); i < rect.position().x() + rect.width(); ++i){
          for(int j = rect.position().y(); j < rect.position().y() + rect.height(); ++j){
            surface[i][j] = color;
            radius = 2;
          }
    }
  }
};
#endif // PAINTER_HPP





//template<>
//uint32_t makeColor<ColorType::Rgba32bpp>(int r, int g, int b, int a);
