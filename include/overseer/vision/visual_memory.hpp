#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <queue>

#include <glog/logging.h>
#include <opencv2/opencv.hpp>


namespace overseer
{
namespace vision
{

typedef uintptr_t imagekey_t;


// VisualMemory is a memory for storing images.
// It is used by the ImageInstance class to store the images.
// The images are stored in a map, and the keys are stored in a queue.
// When the memory is full, the oldest image is removed.
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
    // Image memory size
    imagekey_t max_size;
    // Memory
    std::map<imagekey_t, cv::Mat> memory;
    // Key queue
    std::queue<imagekey_t> keys;
    // Key generator
    imagekey_t generate_image_id(cv::Mat &image);
};

} // namespace vision
} // namespace overseer
