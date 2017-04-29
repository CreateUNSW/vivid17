# CREATE Vivid 2017

## Total Code base for Create Vivid 2017 "Crystallise"

### [Simulator](https://github.com/will-weng/vivid17/tree/master/Simulator)

Mosaic simulator in C++, used to simulate Arduino code (with minimal modification) to see results without actual hardware present. 
<p>
<b>Make a copy of main.cpp and name it to reflect the pattern it tests.</b>
<p>
Only insert code into the "Code to simulate" sections (one for multithreaded code, and another for singlethreaded code, marked out clearly) in {your main}.cpp, run/compile using ./compile_run {your main.cpp} (optionally just run with ./run), where {your main.cpp} is an argument taken in. 
<p>
Use "disp.wait({nanoseconds})" to control the speed of your animation.
<p>
Terminal outputs fps information. Dynamic performance adjustments are disabled (very broken and unnecessary).

### [Image to Code Pattern Converter](https://github.com/will-weng/vivid17/tree/master/Simulator/%5BImage%20to%20Code%5D%20Pattern%20Converter)

Copy Template.bmp and paste into your preferred image editor, and colour in the appropriate panels. When done, run:
<p>
 ./compile_run yourImage.bmp
<p>
 replacing yourImage.bmp with whatever you named the image containing your pattern. Some text will then be outputted to the command line, along with the same text into a file called yourImage.bmp (or whatever you named your image).
<p>
 This text is what the code for the controller uses to create the pattern (and the simulator). Verify that it all works by loading it into the simulator.
<p>
 Format of output text:
 {{R0,G0,B0},{R1,G1,B1}, ... {RN,GN,BN}};
 where Rn is how much red should be in crystal n,
       Gn is how much green should be in crystal n, and
       Bn is how much blue should be in crystal n. 
<p>
These values range from 0 to 255.

### [Lighting pattern](https://github.com/will-weng/vivid17/tree/master/lighting_patterns)

Running light patterns for arduino and led

### [Code](https://github.com/will-weng/vivid17/tree/master/Code)

Graphing library in C

### [Code 2.0](https://github.com/will-weng/vivid17/tree/master/Code%202.0)

Graphing library in C++, used for microcontroller