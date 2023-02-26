#include <iostream>
#include <opencv2/opencv.hpp>
#include "overseer/signal.hpp"


int main(int argc, char** argv)
{
    std::cout << overseer::function1();

    cv::Mat img = cv::imread(argv[1]);
    if (img.empty()) {
        std::cerr << "Failed to load image" << std::endl;
        return 1;
    }
    cv::imshow("Image", img);
    cv::waitKey();
    return 0;

}
