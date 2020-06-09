#include <iostream>
#include <array>
#include "surface.h"
#include "screen.hpp"
#include <thread>
#include <chrono>

int main()
{
    //==================TEXTURE 1========================
    Surface<200,200, ColorType::Rgb24bpp> texture1;

    for(int i = 0; i < texture1.getWidth(); ++i) {
        for(int j = 0; j < texture1.getHeight(); ++j) {
            if(i+j > texture1.getWidth()) {
                texture1.getBuffer()[i][j][0] = 0x50;
                texture1.getBuffer()[i][j][1] = 0xFF;
                texture1.getBuffer()[i][j][2] = 0x20;
            } else {
                texture1.getBuffer()[i][j][0] = 0x50;
                texture1.getBuffer()[i][j][1] = 0x00;
                texture1.getBuffer()[i][j][2] = 0x20;
            }
        }
    }
    //=====================================================

    //==================TEXTURE 2========================
    Surface<200,200, ColorType::Rgb24bpp> texture2;

    for(int i = 0; i < texture2.getWidth(); ++i) {
        for(int j = 0; j < texture2.getHeight(); ++j) {
            if(i*2 > texture2.getWidth()) {
                texture2.getBuffer()[i][j][0] = 0x50;
                texture2.getBuffer()[i][j][1] = 0x1F;
                texture2.getBuffer()[i][j][2] = 0x30;
            } else {
                texture2.getBuffer()[i][j][0] = 0xF0;
                texture2.getBuffer()[i][j][1] = 0x00;
                texture2.getBuffer()[i][j][2] = 0x20;
            }
        }
    }
    //=====================================================

    Screen<decltype(texture1)> screen(texture1.getWidth(), texture1.getHeight());
    screen.init();

    int i = 0;
    do {
        (i%2 == 0) ? screen.draw(texture1) : screen.draw(texture2);
        i++;

        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));


    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(screen.getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
       glfwWindowShouldClose(screen.getWindow()) == 0 );

}
