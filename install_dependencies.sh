#!/bin/bash

# Install dependencies
apt update && apt install -y \
    cmake g++ wget unzip \
    libavcodec-dev libavformat-dev libswscale-dev libgtk2.0-dev
    libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libopenjp2-7-dev

# Create external directory and switch into it
pushd external

# # Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip
unzip opencv.zip
unzip opencv_contrib.zip

# Create build directory and switch into it
mkdir -p build && cd build

# Configure
OPENCV_CMAKE_ARGS=(
  "-DWITH_CUDA=OFF"
  "-DWITH_QT=OFF"
  "-DBUILD_DOCS=OFF"
  "-DBUILD_TESTS=OFF"
  "-DBUILD_PERF_TESTS=OFF"
  "-DBUILD_EXAMPLES=OFF"
  "-DWITH_FFMPEG=ON"
  "-DWITH_GSTREAMER=ON"
  "-DBUILD_opencv_python3=OFF"
  "-DBUILD_opencv_imgproc=ON"
  "-DBUILD_opencv_contrib=ON"
  "-DBUILD_opencv_core=ON"
  "-DBUILD_opencv_highgui=ON"
  "-DBUILD_DOCS=OFF"
  "-DWITH_MSMF=OFF"
  "-DWITH_IPP=OFF"
  "-DBUILD_WITH_STATIC_CRT=OFF"
  "-DBUILD_FAT_JAVA_LIB=OFF"
  "-DBUILD_opencv_apps=OFF"
)
cmake "${OPENCV_CMAKE_ARGS[@]}" -DCMAKE_BUILD_TYPE=Release -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.x/modules ../opencv-4.x

# Build
cmake --build .  --parallel 10

popd