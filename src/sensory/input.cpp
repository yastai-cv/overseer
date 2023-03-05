#include "overseer/sensory/input.hpp"

namespace overseer
{
namespace sensory
{

Input::Input(std::string name, Source *source) : name(name), source(source) {};

Input::~Input()
{
    close();
    // TODO: handle Source deletion
}

std::string Input::get_name()
{
    return name;
}

void Input::collect()
{
    // This is a toy example. In the future, this will be a loop that
    // continuously pulls images from the source and stores them in the
    // queue.
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

int Input::pull()
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

void Input::close()
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    done = true;
    queue_cv.notify_one();
}


} // namespace sensory
} // namespace overseer
