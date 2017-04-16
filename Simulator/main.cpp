// If fails to compile, try sudo ln -s /opt/X11/include/X11 /usr/local/include/X11

// my first program in C++
#include <iostream>
#include "CImg/CImg.h"
using namespace cimg_library;

int main(int argc,char **argv) {

    std::cout << "Sumulator starting\n";

    CImg<unsigned char> img("in.bmp");
    CImg<unsigned char> test(400,400,1,3);  // Define a 400x400 color image with 8 bits per color component.
    
    for(int y = 0; y < 400; y++) {
        for(int x = 0; x < 400; x++) {
            test(x,y) = x * y;
        }
    }

    test.display("Test");


    // CImgDisplay main_disp(img, "Simulator");

    // while(!main_disp.is_closed()) {
    //     main_disp.wait();
        
    // }

    //img.display("Simulator");

    // image.display("out.bmp");

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