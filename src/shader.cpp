#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "shader.h"

GLuint Shader::Load(){

	// Create the shaders
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    GLint result = GL_FALSE;
    int infoLogLength;


	// Compile Vertex Shader
    std::cout << "Compiling vertex shader" << std::endl;
    char const * vertexSourcePointer = vertexShader.c_str();
    glShaderSource(vertexShaderId, 1, &vertexSourcePointer , NULL);
    glCompileShader(vertexShaderId);

	// Check Vertex Shader
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if ( infoLogLength > 0 ){
        std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(vertexShaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        std::cout << &vertexShaderErrorMessage[0] << std::endl;
	}



	// Compile Fragment Shader
    std::cout << "Compiling shader" << std::endl;
    char const * fragmentSourcePointer = fragmentShader.c_str();
    glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer , nullptr);
    glCompileShader(fragmentShaderId);

	// Check Fragment Shader
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if ( infoLogLength > 0 ){
        std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(fragmentShaderId, infoLogLength, nullptr, &fragmentShaderErrorMessage[0]);
        std::cout << &fragmentShaderErrorMessage[0] << std::endl;
	}



	// Link the program
    std::cout << "Linking program" << std::endl;
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

	// Check the program
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if ( infoLogLength > 0 ){
        std::vector<char> programErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(programId, infoLogLength, nullptr, &programErrorMessage[0]);
        std::cout << &programErrorMessage[0] << std::endl;
	}

	
    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);
	
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}


