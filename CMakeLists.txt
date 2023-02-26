# CMake minimum required version
cmake_minimum_required(VERSION 3.25.2)

# Project name and version
project(overseer VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Options for building
OPTION(OVERSEER_BUILD_TEST "Build tests" ON)
OPTION(OVERSEER_BUILD_EXT_LIBS "Build external libraries" ON)

# Add include directories
include_directories(include)

# Add source files
set(SOURCES
    src/main.cpp
    # src/overseer.cpp
    # src/signal.cpp
    # src/cognition/task.cpp
    # src/perception/cortex_worker.cpp
    # src/sensory/sensory_input.cpp
    # src/sensory/sensory_pathway.cpp
    # src/vision/image.cpp
    # src/vision/visual_memory.cpp
)

# Add executable target
add_executable(overseer ${SOURCES})

# Add testing subdirectory
add_subdirectory(tests)
