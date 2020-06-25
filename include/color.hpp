#ifndef COLOR_H
#define COLOR_H
#include <cstdint>

enum class ColorType {
    BlackAndWhite1bpp,
    Grayscale8bpp,
    Rgb16bpp,
    Rgb24bpp,
    Rgba32bpp
};

template<ColorType colorType>
class Color;

template<>
class Color<ColorType::Rgba32bpp> {
public:
  Color(){}
  Color(int r, int g, int b, int a) {
    m_rgba = static_cast<uint32_t>((r << 24) & (g << 16) & (b << 8) & a);
  }
private:
  std::uint32_t m_rgba;

};

template<>
class Color<ColorType::Rgb24bpp> {
public:
  Color(){}
  Color(int r, int g, int b) {
    m_rgb[0] = static_cast<std::uint8_t>(b);
    m_rgb[1] = static_cast<std::uint8_t>(g);
    m_rgb[2] = static_cast<std::uint8_t>(r);
  }
private:
  std::uint8_t m_rgb[3];

};

#endif // COLOR_H
