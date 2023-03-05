# Overseer

The overseer focuses its eyes toward scouting and revealing the presence of hidden enemies, wherever they may lurk

## Project Struture

```bash
project/
├── CMakeLists.txt
├── include/
│   └── my_project/
│       ├── header1.hpp
│       └── header2.hpp
├── src/
│   ├── main.cpp
│   ├── source1.cpp
│   └── source2.cpp
├── tests/
│   ├── CMakeLists.txt
│   └── test1.cpp
└── build/
```

## Requirements

```bash
./install_dependencies.sh
```

## Build

Build the project for release

```bash
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .  --parallel $(nproc) --target overseer
```

Build the project for debug

```bash
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .  --parallel $(nproc)
pushd tests
./overseer_test_main
popd
```

Run the program with

```bash
cd build
GLOG_logtostderr=1 ./overseer
```

## Third-Party Libraries

This project was build using these libraries:

* Image Processing: [OpenCV2](https://opencv.org/)
* Testing: [GoogleTest](https://github.com/google/googletest)
* Logging: [GLog](https://github.com/google/glog#user-guide)
