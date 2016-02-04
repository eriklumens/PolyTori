# PolyTori
Displaying toric data and computing various properties for the spaces (and Calabi-Yau hypersurfaces) they represent.

## Building on Linux

Building on Linux requires the following libraries:

- `OpenGL`
- `GLEW`
- `GLFW` (>= 3) 

Also `CMake` is required for building

To get the appropriate version of GLEW, just run

    $ sudo apt-get install libglew-dev

To properly install GLFW, obtain GLFW source files from their official website, then run

    $ sudo apt-get install xorg-dev libglu1-mesa-dev
    
After which you go to downloaded source files directory and run

    $ cmake .
    $ make
    $ sudo make install

After we have installed all the necessary libraries, navigate to the root directory of the repository and run

    $ cd build
    $ cmake .
    $ make

Then open `./bin/PolyToriApp` to run the program. Most of the functionality is at the moment in `application/src/main.cpp`, if you want to change how to program works you'll have to do it there. 
