ARG base=base_cpu

############################
# Install CPU dependencies #
############################
FROM ubuntu:20.04 AS base_cpu

# Install dependencies
RUN apt update && apt install -y \
    cmake g++ wget unzip \
    libavcodec-dev libavformat-dev libswscale-dev libgtk2.0-dev \
    libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libopenjp2-7-dev
RUN apt-get clean && rm -rf /var/lib/apt/lists/*
RUN mkdir /app
WORKDIR /app

# Install external dependencies
RUN mkdir /app/external
WORKDIR /app/external

# Download and unpack sources
ENV USE_GPU=0
RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
RUN wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip
RUN unzip opencv.zip
RUN unzip opencv_contrib.zip
RUN rm opencv.zip opencv_contrib.zip
RUN ./build_external.sh

# Copy source code
COPY ./CMakeLists.txt /app/CMakeLists.txt
COPY ./src /app/src
COPY ./include /app/include
COPY ./external /app/external

# Create build directory and switch into it
RUN mkdir /app/build
WORKDIR /app/build


####################################
# Build the project for production #
####################################
FROM {base} AS prod
RUN cmake --build .  --parallel $(nproc)


#####################################
# Build the project for development #
#####################################
FROM {base} as dev
RUN cmake -DCMAKE_BUILD_TYPE=Debug --build .  --parallel $(nproc)
