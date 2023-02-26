#include <iostream>
#include <opencv2/opencv.hpp>
#include "overseer/overseer.hpp"


int main(int argc, char **argv)
{
    overseer::Overseer overseer;
    overseer.run(argv[1]);
}
