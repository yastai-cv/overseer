#pragma once
#include <string>
#include <memory>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
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



class SensoryInput
{
public:
    SensoryInput(std::string name, Source *source) : name(name), source(source) {};

    void collect()
    {
        int i = 0;
        while (!done) {
            std::unique_lock<std::mutex> lock(queue_mutex);
            queue.push(i++);
            lock.unlock();
            queue_cv.notify_one();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        queue_cv.notify_one();
    }

    // std::unique_ptr<vision::ImageInstance> next()
    int next()
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cv.wait(lock, [this](){ return !queue.empty() || done; });

        if (done && queue.empty()) {
            return -1;
        }

        int value = queue.front();
        queue.pop();

        return value;
    }

    void close()
    {
        done = true;
    }

private:
    std::string name;
    Source *source;
    std::mutex queue_mutex;
    std::condition_variable queue_cv;
    // std::queue<std::unique_ptr<vision::ImageInstance>> queue;
    std::queue<int> queue;
    bool done = false;
};

} // namespace sensory
} // namespace overseer