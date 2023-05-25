cmake_minimum_required(VERSION 3.20.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

execute_process ( COMMAND git clone https://github.com/Draune/dStruct.git
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ ) 

project(dAsciiArt)

set(SRCS
    sources/main.cpp
    sources/sort_char.cpp
    sources/convert.cpp
    sources/save.cpp
    sources/font.cpp
    sources/display.cpp)
    
set(HEADERS 
    headers/sort_char.hpp
    headers/convert.hpp
    headers/save.hpp
    headers/font.hpp
    headers/display.hpp)

add_executable(dAsciiArt ${SRCS} ${HEADERS})


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( dAsciiArt ${OpenCV_LIBS} )

add_subdirectory(dStruct)
target_link_libraries(dAsciiArt dStruct)

target_link_libraries(dAsciiArt ncurses)