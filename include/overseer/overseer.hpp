#pragma once

#include <iostream>
#include <memory>

#include <glog/logging.h>
#include <opencv2/opencv.hpp>

#include "overseer/vision/image.hpp"
#include "overseer/vision/visual_memory.hpp"
#include "overseer/sensory/input.hpp"
#include "overseer/sensory/pathway.hpp"
#include "overseer/sensory/sense.hpp"
#include "overseer/sensory/signal.hpp"


namespace overseer {

// Overseer is the main class of the overseer library.
// It handles multiple inputs sources, and add perceptual information to the
// images instances. Then, it can be used by an application to perform cognitive
// tasks.
class Overseer {
public:
    Overseer();
    // Overseer entry point.
    int run(const char *image_path);
private:
    // TODO: Work in progress
    // Visual memory
    std::shared_ptr<vision::VisualMemory> memory;
    vision::ImageInstance image;
};

} // namespace overseer
