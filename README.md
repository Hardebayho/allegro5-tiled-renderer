Renders Tiled maps for the Allegro 5 library.

Uses the Tmxparser library from https://github.com/sainteos/tmxparser

Note: I already integrated the tmxparser library into the project so you don't have to download separately.

# To compile
If your build system is CMake, you can clone the repository and copy the contents inside your project and just do an `add_subirectory('path/to/the/lib')`. To link the library into your own project, you'll add in your own CMakeLists.txt, a `target_link_libraries(${PROJECT_NAME} Allegro5TiledRenderer)`

You can also build the library as a shared library. To do this do inside the top-level directory for the project:
`mkdir build && cd build && cmake ..`
`make`
`sudo make install` if you want to install the library into your system.
