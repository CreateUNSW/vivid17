// If fails to compile, try sudo ln -s /opt/X11/include/X11 /usr/local/include/X11

// my first program in C++
#include <iostream>
#include "CImg/CImg.h"
using namespace cimg_library;

int main(int argc,char **argv) {

    std::cout << "Hello World!\n";


    CImg<unsigned char> image("in.bmp"), visu(500,400,1,3,0);

    image.display("out.bmp");

    // CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile");
    // main_disp.wait();

    // visu.display("Image");

    // CImg<unsigned char> img(640,400,1,3);  // Define a 640x400 color image with 8 bits per color component.
    // img.fill(0);                           // Set pixel values to 0 (color : black)
    // unsigned char purple[] = { 255,0,255 };        // Define a purple color
    // img.draw_text(100,100,"Hello World",purple); // Draw a purple "Hello world" at coordinates (100,100).
    // img.display("My first CImg code");             // Display the image in a display window.
    
    return 0;
}