#ifndef SURFACE_H
#define SURFACE_H

#include <iostream>
#include <array>
enum class ColorType {
    BlackAndWhite1bpp,
    Grayscale8bpp,
    Rgb16bpp,
    Rgb24bpp,
    Rgba32bpp
};


template<std::size_t width, std::size_t height, ColorType colorType>
class Surface {

    static constexpr int numBytes(ColorType color){

        int bpp = 0;

        switch(color){
        case ColorType::BlackAndWhite1bpp:
            bpp = 1;
            break;
        case ColorType::Grayscale8bpp:
            bpp = 8;
            break;
        case ColorType::Rgb16bpp:
            bpp = 16;
            break;
        case ColorType::Rgb24bpp:
            bpp = 24;
            break;
        case ColorType::Rgba32bpp:
            bpp = 32;
            break;
        }

        int nBytes = 0;
        (bpp%8 == 0 ) ? (nBytes = bpp/8) : (nBytes = bpp/8+1);
        return nBytes;
    }

public:
    typedef std::array<std::array<std::uint8_t[numBytes(colorType)], height>, width> ScreenBuffer;

    inline std::size_t getWidth() const {
        return width;
    }

    inline std::size_t getHeight() const{
        return height;
    }

    inline ColorType getColorType() const {
        return colorType;
    }

    ScreenBuffer& getBuffer() {
        return m_screenBuffer;
    }




private:
    ScreenBuffer m_screenBuffer;

};

#endif // SURFACE_H
