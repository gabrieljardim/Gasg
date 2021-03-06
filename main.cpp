#include <iostream>
#include <array>
#include "surface.h"
#include "screen.hpp"
#include "painter.hpp"
#include <thread>
#include <chrono>
int main()
{
  const int testWidth = 500;
  const int testHeight = 500;
    //==================TEXTURE 1========================
    Surface<testWidth,testHeight, ColorType::Rgb24bpp> texture1;

    for(std::size_t i = 0; i < texture1.getWidth(); ++i) {
        for(std::size_t j = 0; j < texture1.getHeight(); ++j) {
            if(i+j > texture1.getWidth()) {
                texture1[i][j] = Color<ColorType::Rgb24bpp>(0x50, 0xFF, 0x20);
            } else {
              texture1[i][j] = Color<ColorType::Rgb24bpp>(0x50, 0x00, 0x20);
            }
        }
    }
    //=====================================================

    //==================TEXTURE 2========================
    Surface<testWidth,testHeight, ColorType::Rgb24bpp> texture2;

    for(std::size_t i = 0; i < texture2.getWidth(); ++i) {
        for(std::size_t j = 0; j < texture2.getHeight(); ++j) {
            if(i*2 > texture2.getWidth()) {
                texture2[i][j] = Color<ColorType::Rgb24bpp>(0x50, 0x1F, 0x30);
            } else {
                texture2[i][j] = Color<ColorType::Rgb24bpp>(0xF0, 0x00, 0x20);
            }
        }
    }
    //=====================================================


    //==================TEXTURE 3========================
    Surface<testWidth,testHeight, ColorType::Rgb24bpp> texture3;
    Painter<ColorType::Rgb24bpp> painter;

    auto texture3Width = texture3.getWidth();
    auto texture3Height = texture3.getHeight();

    painter.drawRectangleFill(texture3, Rectangle(texture3Width, texture3Height, Point2d(0, 0)), Color<ColorType::Rgb24bpp>(200,200,200));
    painter.drawRectangleFill(texture3, Rectangle(300, 10, Point2d(10, 10)), Color<ColorType::Rgb24bpp>(50, 20, 150));
    painter.drawRectangleFill(texture3, Rectangle(310, 10, Point2d(10, 30)), Color<ColorType::Rgb24bpp>(50, 20, 150));
    painter.drawRectangleFill(texture3, Rectangle(320, 10, Point2d(10, 50)), Color<ColorType::Rgb24bpp>(0, 255, 0));
    painter.drawRectangleFill(texture3, Rectangle(330, 10, Point2d(10, 70)), Color<ColorType::Rgb24bpp>(0, 0, 255));

    //=====================================================



    //==================TEXTURE 4========================
    Surface<testWidth,testHeight, ColorType::Rgb24bpp> texture4;
    //Painter<ColorType::Rgb24bpp> painter;

    auto texture4Width = texture3.getWidth();
    auto texture4Height = texture3.getHeight();

    for(std::size_t i = 0; i < texture4Width; ++i) {
        for(std::size_t j = 0; j < texture4Height; ++j) {
            if(i == j) {
                texture4[i][j] = Color<ColorType::Rgb24bpp>(255, 255, 255);
            }
        }
    }
    //=====================================================




    Screen screen(texture1.getWidth(), texture1.getHeight());
    screen.init();

    int i = 0;
    do {
        switch(i%4) {
        case 0:
          screen.draw(texture1);
          break;
        case 1:
          screen.draw(texture2);
          break;
        case 2:
          screen.draw(texture3);
          break;
        case 3:
          screen.draw(texture4);
          break;
        }
        i++;


        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(screen.getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
       glfwWindowShouldClose(screen.getWindow()) == 0 );

}
