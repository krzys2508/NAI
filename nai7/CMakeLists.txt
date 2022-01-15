cmake_minimum_required(VERSION 3.20)
project(nai7)

set(CMAKE_CXX_STANDARD 14)

add_executable(nai7 nai7.cpp)

set(OpenCV_DIR "/usr/local/Cellar/opencv/4.5.3_3/include/opencv4/opencv2")
set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

target_link_libraries(nai7 ${OpenCV_LIBS})
