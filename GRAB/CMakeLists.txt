cmake_minimum_required(VERSION 2.8)

project(robomaster)
SET(CMAKE_BUILE_TYPE DEBUG)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14 -lv4l1 -lv4l2 -pthread")
SET(BIN_NAME "run")

FIND_PACKAGE(OpenCV 3.4.0 REQUIRED)
FIND_PACKAGE(Threads)

include_directories(${OpenCV_INCLUDE_DIRS})
MESSAGE(STATUS "Project:GRAB")
MESSAGE(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}")
MESSAGE(STATUS "OpenCVlibrarystatus:")
MESSAGE(STATUS "version: ${OpenCV_VERSION}")
MESSAGE(STATUS " libraries: ${OpenCVLIBS}")
MESSAGE(STATUS "includepath:${PROJECT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS}")

FILE(GLOB_RECURSE sourcefiles)
ADD_EXECUTABLE(${BIN_NAME} main.cpp ${sourcefiles})

#aux_source_directory(. ALL_SRCS)
#add_executable(robomaster_1_6 ${ALL_SRCS})

TARGET_LINK_LIBRARIES(${BIN_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${BIN_NAME} ${OpenCV_LIBS})

