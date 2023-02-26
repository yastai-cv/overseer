#pragma once
#include <memory>
#include "overseer/vision/image.hpp"
#include "overseer/vision/visual_memory.hpp"


namespace overseer {
class Overseer {
public:
    Overseer();
    int run(const char *image_path);
private:
    std::shared_ptr<vision::VisualMemory> memory;
    vision::ImageInstance image;
};

} // namespace overseer
