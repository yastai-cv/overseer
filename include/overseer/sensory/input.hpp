#pragma once

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include <glog/logging.h>
#include <opencv2/opencv.hpp>

#include <overseer/vision/image.hpp>


namespace overseer
{
namespace sensory
{

class Source
{
public:
    virtual std::unique_ptr<vision::ImageInstance> get_image_instance() = 0;
};

class ImageFileSource : public Source
{
};

class VideoFileSource : public Source
{
};

class CameraSource : public Source
{
};


// This class is responsible for collecting images from a source and
// storing them in a queue. The queue is then consumed by the
// Pathway class, for later processing.
class Input
{
public:
    // TODO: Use unique pointer with source
    Input(std::string name, Source *source);
    ~Input();

    // Retrieve the name of the input.
    std::string get_name();

    // Retrieve the next image instance from the source.
    void collect();

    // std::unique_ptr<vision::ImageInstance> next()
    int pull();

    // Stop the collection, and notify wherever is waiting for the next image.
    // This should be called when the program is exiting.
    void close();

private:
    // The name of the input.
    std::string name;
    // The source of the input.
    Source *source;
    // std::unique_ptr<Source> source;
    // The queue of retrieved images and thread control variables.
    std::mutex queue_mutex;
    std::condition_variable queue_cv;
    std::queue<int> queue;
    // std::queue<std::unique_ptr<vision::ImageInstance>> queue;

    // Indicates whether the collection has stopped.
    bool done = false;
};

} // namespace sensory
} // namespace overseer