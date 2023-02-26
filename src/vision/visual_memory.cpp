#include "overseer/vision/visual_memory.hpp"


namespace overseer {
namespace vision {

VisualMemory::VisualMemory(imagekey_t max_size)
{
    this->max_size = max_size;
}

imagekey_t VisualMemory::generate_image_id(cv::Mat &image)
{
    imagekey_t id = reinterpret_cast<imagekey_t>(&image);
    std::cout << "Image id: " << id << std::endl;
    return id;
}


imagekey_t VisualMemory::put_image(cv::Mat image)
{
    imagekey_t id = generate_image_id(image);
    if (keys.size() >= max_size)
    {
        imagekey_t key = keys.front();
        keys.pop();
        memory.erase(key);
    }
    memory[id] = image.clone();
    keys.push(id);
    return id;
}

void VisualMemory::print_memory()
{
    std::cout << "Allocated keys" << std::endl;
    std::queue<imagekey_t> copy_keys = keys;
    while (copy_keys.size() > 0)
    {
        std::cout << "Key: " << copy_keys.front() << std::endl;
        copy_keys.pop();
    }

    std::cout << "Memory size: " << memory.size() << std::endl;
    for (auto &item : memory)
    {
        std::cout << "Key: " << item.first << std::endl;
    }
}


const cv::Mat &VisualMemory::get_image(imagekey_t key)
{
    return memory[key];
}

} // namespace vision
} // namespace overseer
