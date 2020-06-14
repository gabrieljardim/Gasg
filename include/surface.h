#ifndef SURFACE_H
#define SURFACE_H

#include <iostream>
#include <array>
#include "color.hpp"

template<std::size_t width, std::size_t height, ColorType colorType>
class Surface : public std::array<std::array<Color<colorType>, height>, width> {

public:
    Surface(){}
    typedef std::array<std::array<Color<colorType>, height>, width> ScreenBuffer;

    inline std::size_t getWidth() const {
        return width;
    }

    inline std::size_t getHeight() const{
        return height;
    }

    inline ColorType getColorType() const {
        return colorType;
    }
};

#endif // SURFACE_H
