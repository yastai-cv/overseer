#pragma once
#include <string>
#include <memory>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
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



class Input
{
public:
    // Use unique pointer with source
    Input(std::string name, Source *source) : name(name), source(source) {};

    std::string get_name() {
        return name;
    }

    bool is_done() {
        return done;
    }

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
    int pull()
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cv.wait(lock, [this](){ return !queue.empty() || done; });

        if (done && queue.empty()) {
            // TODO: use a cleaner way to break out of the loop
            return -1;
        }

        int value = queue.front();
        queue.pop();
        lock.unlock();
        return value;
    }

    void close()
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        done = true;
        queue_cv.notify_one();
    }

private:
    std::string name;
    // std::unique_ptr<Source> source;
    Source *source;
    std::mutex queue_mutex;
    std::condition_variable queue_cv;
    // std::queue<std::unique_ptr<vision::ImageInstance>> queue;
    std::queue<int> queue;
    bool done = false;
};

} // namespace sensory
} // namespace overseer