#ifndef SCREEN_HPP
#define SCREEN_HPP

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include <texture.hpp>

#include "surface.h"

template<typename T>
class Screen {
public:
    Screen(std::size_t width, std::size_t height) :
    m_width(width),
    m_height(height){
    }

    int init(){

        // Initialise GLFW
        if( !glfwInit() )
        {
            fprintf( stderr, "Failed to initialize GLFW\n" );
            return -1;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Open a window and create its OpenGL context
        m_window = glfwCreateWindow( m_width, m_height, "Tutorial 05 - Textured Cube", NULL, NULL);
        if( m_window == NULL ){
            fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(m_window);

        // Initialize GLEW
        glewExperimental = true; // Needed for core profile
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW\n");
            return -1;
        }

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

        // Dark blue background
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        // Create and compile our GLSL program from the shaders
        m_programId = Shader::Load();

        // Get a handle for our "MVP" uniform
        m_matrixId = glGetUniformLocation(m_programId, "MVP");

        // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        // Camera matrix
        glm::mat4 View       = glm::lookAt(
                                    glm::vec3(0,0,3), // Camera is at (4,3,3), in World Space
                                    glm::vec3(0,0,0), // and looks at the origin
                                    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                               );
        // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model      = glm::mat4(1.0f);
        // Our ModelViewProjection : multiplication of our 3 matrices

        m_mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

            static const GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
             1.0f,-1.0f,-1.0f,
             1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
             1.0f,-1.0f,-1.0f

        };

        // Two UV coordinatesfor each vertex. They were created with Blender.
        static const GLfloat g_uv_buffer_data[] = {
            -1.0f,-1.0f,
            -1.0f, 1.0f,
             1.0f,-1.0f,
             1.0f, 1.0f,
            -1.0f, 1.0f,
             1.0f,-1.0f
        };

        glGenBuffers(1, &m_vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glGenBuffers(1, &m_uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

        return 0;


    }

    void draw(T& surface ) {

        auto data = surface.data();
        auto width =  surface.getWidth();
        auto height = surface.getHeight();
        auto colortype = surface.getColorType();


        auto textureId = Texture::generate(width, height, colortype, static_cast<void*>(data));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(m_programId);
        glUniformMatrix4fv(m_matrixId, 1, GL_FALSE, &m_mvp[0][0]);

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(textureId, 0);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_uvbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                                // size : U+V => 2
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 2*3);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // Swap buffers
        glfwSwapBuffers(m_window);
        glDeleteTextures(1, &textureId);

    }

    GLFWwindow* getWindow() {
        return m_window;
    }



private:
    std::size_t m_width;
    std::size_t m_height;
    GLFWwindow* m_window;

    GLuint  m_programId;
    GLuint m_matrixId;
    glm::mat4 m_mvp;
    GLuint m_vertexbuffer;
    GLuint m_uvbuffer;

};

#endif // SCREEN_HPP

