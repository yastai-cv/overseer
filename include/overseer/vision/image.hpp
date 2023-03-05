#pragma once

#include <memory>

#include <glog/logging.h>
#include <opencv2/opencv.hpp>

#include "overseer/vision/visual_memory.hpp"


namespace overseer
{
namespace vision
{

// An ImageInstance is a wrapper around an image. It is responsible for
// loading the image, and storing it in the VisualMemory.
// It also provides a way to retrieve the image from the VisualMemory.
// This is done to avoid copying the image, and reduce the memory usage.
class ImageInstance
{
public:
    ImageInstance();
    ImageInstance(std::shared_ptr<VisualMemory> memory);
    // Load an image from a file.
    int load(const char *image_path);
    // Copy an image from a cv::Mat.
    int load(const cv::Mat &image);
    // Retrieve a read-only reference to the image.
    const cv::Mat& get_image();

private:
    // Image memory, for storing the image.
    std::shared_ptr<VisualMemory> memory;
    // Image key, for retrieving the image from the memory.
    imagekey_t image_key;
    // Push the image to the memory.
    void push_image_to_memory(const cv::Mat &image);
    // Retrieve the image from the memory.
    const cv::Mat& retrieve_image_from_memory();
};

} // namespace vision
} // namespace overseer
