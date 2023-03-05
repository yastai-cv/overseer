#include "overseer/sensory/signal.hpp"

namespace overseer
{
namespace sensory
{

Signal::Signal(std::string name) : name(name) {};

Signal::~Signal()
{
    close();
};

void Signal::push(int value)
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    queue.push(value);
    queue_cv.notify_one();
}

void Signal::broadcast()
{
    while (!done) {
        // Wait for a value to be pushed
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cv.wait(lock, [this](){ return !queue.empty() || done; });
        if (done && queue.empty()) {
            break;
        }
        int value = queue.front();
        queue.pop();
        lock.unlock();
        // Notify subscribers
        notify(value);
    }
}

void Signal::subscribe()
{
    // Not implemented
}

void Signal::unsubscribe()
{
    // Not implemented
}

void Signal::close()
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    done = true;
    queue_cv.notify_one();
}

void Signal::notify(int value)
{
    std::cout << "Notified from " << name << ": " << value << std::endl;
}

} // namespace sensory
} // namespace overseer