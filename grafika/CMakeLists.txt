cmake_minimum_required(VERSION 3.6)
project(grafika)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -fpermissive")

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)


include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})

file(GLOB SOURCE_FILES
        *.cpp
        *.h
        )

add_executable(grafika ${SOURCE_FILES})

target_link_libraries (grafika ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} pthread)