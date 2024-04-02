cmake_minimum_required(VERSION 3.14)
project(SFMLSD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Paddle.h
        Ball.h
)
add_executable(SFMLSD ${SOURCE_FILES})
include_directories(/usr/local/include)

configure_file(images/Hello.png images/Hello.png COPYONLY)
configure_file(images/ping_pong.jpeg images/ping_pong.jpeg COPYONLY)
configure_file(font/font.ttf font/font.ttf COPYONLY)


find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(SFMLSD sfml-system sfml-window sfml-graphics sfml-audio sfml-network)