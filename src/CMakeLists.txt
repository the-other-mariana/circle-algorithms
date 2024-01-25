cmake_minimum_required(VERSION 3.18)
project(YourProjectName)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)

target_link_libraries(main ${OpenCV_LIBS})
