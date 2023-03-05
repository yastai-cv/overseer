#include <iostream>
#include <opencv2/opencv.hpp>
#include "overseer/overseer.hpp"


int main(int argc, char **argv)
{
    overseer::Overseer overseer;
    return overseer.run(argv[1]);
}