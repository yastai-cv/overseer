#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <opencv2/opencv.hpp>


namespace overseer
{
namespace vision
{

typedef uintptr_t imagekey_t;

class VisualMemory
{
public:
    VisualMemory(imagekey_t max_size=999);

    // Put image to memory
    imagekey_t put_image(cv::Mat image);

    // Get image from memory
    const cv::Mat& get_image(imagekey_t key);

    // Display memory content
    void print_memory();

private:
    // Image memory
    imagekey_t max_size;
    std::map<imagekey_t, cv::Mat> memory;
    std::queue<imagekey_t> keys;

    // Key generator
    imagekey_t generate_image_id(cv::Mat &image);
};

} // namespace vision
} // namespace overseer
