#!/bin/bash

# Configure
# If USE_GPU is available in the environment, then we will build OpenCV with CUDA support
if [ -z "$USE_GPU" ]; then
  OPENCV_CUDA_CMAKE_ARGS=(
    "-DWITH_CUDA=OFF"
  )
else
  OPENCV_CUDA_CMAKE_ARGS=(
    "-DWITH_CUDA=ON"
    # "-DCUDA_ARCH_BIN=7.5"
    # "-DCUDA_ARCH_PTX=7.5"
    # "-DCUDA_FAST_MATH=ON"
    # "-DCUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda"
    # "-DCUDA_NVCC_FLAGS=--expt-relaxed-constexpr"
    # "-DCUDA_GENERATION=Auto"
    # "-DWITH_CUBLAS=ON"
    # "-DWITH_CUFFT=ON"
    # "-DWITH_NVCUVID=ON"
    # "-DWITH_NVCUVID=ON"
    # "-DWITH_CUDNN=ON"
    # "-DCUDNN_INCLUDE_DIR=/usr/include"
    # "-DCUDNN_LIBRARY=/usr/lib/x86_64-linux-gnu/libcudnn.so"
    # "-DCUDNN_VERSION=7.6.5"
    # "-DCUDA_cublas_LIBRARY=/usr/lib/x86_64-linux-gnu/libcublas.so"
    # "-DCUDA_cufft_LIBRARY=/usr/lib/x86_64-linux-gnu/libcufft.so"
    # "-DCUDA_curand_LIBRARY=/usr/lib/x86_64-linux-gnu/libcurand.so"
    # "-DCUDA_cusolver_LIBRARY=/usr/lib/x86_64-linux-gnu/libcusolver.so"
    # "-DCUDA_cusparse_LIBRARY=/usr/lib/x86_64-linux-gnu/libcusparse.so"
    # "-DCUDA_nppc_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppc.so"
    # "-DCUDA_nppi_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppi.so"
    # "-DCUDA_npps_LIBRARY=/usr/lib/x86_64-linux-gnu/libnpps.so"
    # "-DCUDA_nppial_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppial.so"
    # "-DCUDA_nppicc_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppicc.so"
    # "-DCUDA_nppicom_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppicom.so"
    # "-DCUDA_nppidei_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppidei.so"
    # "-DCUDA_nppif_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppif.so"
    # "-DCUDA_nppig_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppig.so"
    # "-DCUDA_nppim_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppim.so"
    # "-DCUDA_nppist_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppist.so"
    # "-DCUDA_nppisu_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppisu.so"
    # "-DCUDA_nppitc_LIBRARY=/usr/lib/x86_64-linux-gnu/libnppitc.so"
  )
fi

# Build OpenCV Arguments
OPENCV_CMAKE_ARGS=(
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
  "-DBUILD_opencv_apps=OFF"
  "-DBUILD_DOCS=OFF"
  "-DWITH_MSMF=OFF"
  "-DWITH_IPP=OFF"
  "-DBUILD_WITH_STATIC_CRT=OFF"
  "-DBUILD_FAT_JAVA_LIB=OFF"
)

cmake "${OPENCV_CUDA_CMAKE_ARGS[@]}" "${OPENCV_CMAKE_ARGS[@]}" -DCMAKE_BUILD_TYPE=Release -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.x/modules ../opencv-4.x
