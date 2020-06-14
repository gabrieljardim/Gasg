#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

namespace Shader {
const static std::string fragmentShader = "#version 330 core                                         \n"
                                          "in vec2 UV;                                               \n"
                                          "out vec3 color;                                           \n"
                                          "uniform sampler2D myTextureSampler;                       \n"
                                          "void main(){                                              \n"
                                          "    color = texture( myTextureSampler, UV ).rgb;          \n"
                                          "}                                                           ";
const static std::string vertexShader = "#version 330 core                                           \n"
                                        "layout(location = 0) in vec3 vertexPosition_modelspace;     \n"
                                        "layout(location = 1) in vec2 vertexUV;                      \n"
                                        "out vec2 UV;                                                \n"
                                        "uniform mat4 MVP;                                           \n"
                                        "void main(){                                                \n"
                                        "    gl_Position =  MVP * vec4(vertexPosition_modelspace,1); \n"
                                        "    UV = vertexUV;                                          \n"
                                        "}                                                             ";

GLuint Load();

}
#endif
