#include <iostream>
#include <opencv2/opencv.hpp>
#include <glog/logging.h>
#include "overseer/overseer.hpp"


int main(int argc, char **argv)
{
    google::InitGoogleLogging(argv[0]);
    overseer::Overseer overseer;
    return overseer.run(argv[1]);
}