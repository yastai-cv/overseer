#include <iostream>
#include <opencv2/opencv.hpp>
#include "overseer/overseer.hpp"


int overseer::Overseer::run(const char *image_path)
{
    cv::Mat img = cv::imread(image_path);
    if (img.empty())
    {
        std::cerr << "Failed to load image" << std::endl;
        return 1;
    }
    cv::imshow("Image", img);
    cv::waitKey();
    return 0;
}
