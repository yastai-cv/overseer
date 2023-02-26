#include "overseer/vision/image.hpp"


namespace overseer {
namespace vision
{

ImageInstance::ImageInstance()
{
    this->memory = std::make_shared<VisualMemory>();
}

ImageInstance::ImageInstance(std::shared_ptr<VisualMemory> memory)
{
    this->memory = memory;
}

int ImageInstance::load(const char *image_path)
{
    cv::Mat image = cv::imread(image_path);
    if (image.empty())
    {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }
    this->push_image_to_memory(image);
    return 0;
}

int ImageInstance::load(const cv::Mat &image)
{
    if (image.empty())
    {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }
    this->push_image_to_memory(image);
    return 0;
}

const cv::Mat& ImageInstance::get_image()
{
    return this->retrieve_image_from_memory();
}

void ImageInstance::push_image_to_memory(const cv::Mat &image)
{
    this->image_key = this->memory->put_image(image);
}

const cv::Mat& ImageInstance::retrieve_image_from_memory()
{
    return this->memory->get_image(this->image_key);
}

} // namespace vision
} // namespace overseer
