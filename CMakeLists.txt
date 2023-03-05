# CMake minimum required version
cmake_minimum_required(VERSION 3.25.2)

# Project name and version
project(overseer VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Options for building
OPTION(OVERSEER_BUILD_TEST "Build tests" ON)
OPTION(OVERSEER_BUILD_EXT_LIBS "Build external libraries" ON)

# Add include directories
include_directories(include)

# Add source files
set(SOURCES
    src/main.cpp
    src/overseer.cpp
    # src/cognition/task.cpp
    # src/perception/cortex_worker.cpp
    src/sensory/signal.cpp
    src/sensory/input.cpp
    src/sensory/pathway.cpp
    src/sensory/sense.cpp
    src/vision/image.cpp
    src/vision/visual_memory.cpp
)

# Add external libraries
set(CMAKE_PREFIX_PATH "external/build" ${CMAKE_PREFIX_PATH})

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add executable target
add_executable(overseer ${SOURCES})

# Link executable target with OpenCV libraries
target_link_libraries(overseer ${OpenCV_LIBS})
# target_link_libraries(overseer ${OpenCV_LIBS} opencv_contrib)

# Add testing subdirectory
add_subdirectory(tests)
