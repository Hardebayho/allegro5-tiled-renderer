cmake_minimum_required(VERSION 2.8)

project(Allegro5TiledRenderer)

option(COMPILE_TEST "Compile the test executable of the library. (Default: ON)" ON)

add_subdirectory(lib/tmxparser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

include_directories(${CMAKE_SOURCE_DIR}/include)

set(headers
  include/MapRenderer.h
  include/GroupLayerRenderer.h
  include/ObjectLayerRenderer.h
  include/RendererTileset.h
  include/TileLayerRenderer.h
  include/ImageLayerRenderer.h
)

set(srcs
  src/MapRenderer.cpp
  src/GroupLayerRenderer.cpp
  src/ObjectLayerRenderer.cpp
  src/RendererTileset.cpp
  src/TileLayerRenderer.cpp
  src/ImageLayerRenderer.cpp
)

add_library(Allegro5TiledRenderer SHARED ${srcs})

target_include_directories(Allegro5TiledRenderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Allegro5TiledRenderer tmxparser allegro allegro_image)

install(TARGETS Allegro5TiledRenderer
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

install(FILES ${headers}
        DESTINATION include/Allegro5TiledRenderer)

add_executable(test_lib test/test.cpp)
target_link_libraries(test_lib Allegro5TiledRenderer allegro allegro_image)
