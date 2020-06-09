#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "surface.h"


namespace Texture {
GLuint generate(std::size_t width, std::size_t height, ColorType colorType, void* data);
}


#endif
