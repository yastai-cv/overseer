#pragma once
#include <memory>
#include <opencv2/opencv.hpp>
#include "overseer/vision/visual_memory.hpp"


namespace overseer
{
namespace vision
{
class ImageInstance
{
public:
    ImageInstance();
    ImageInstance(std::shared_ptr<VisualMemory> memory);
    int load(const char *image_path);
    int load(const cv::Mat &image);
    const cv::Mat& get_image();

private:
    // Image memory
    std::shared_ptr<VisualMemory> memory;
    imagekey_t image_key;

    void push_image_to_memory(const cv::Mat &image);
    const cv::Mat& retrieve_image_from_memory();
};

} // namespace vision
} // namespace overseer
