#pragma once
#include <string>
#include <mutex>
#include <queue>


namespace overseer
{
namespace sensory
{
class Signal
{
public:
    Signal() {};
    Signal(std::string name) : name(name) {};

    void push(int value) {
        std::lock_guard<std::mutex> lock(queue_mutex);
        queue.push(value);
        queue_cv.notify_one();
    }

    void broadcast() {
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
    void subscribe();
    void unsubscribe();
    void close() {
        std::lock_guard<std::mutex> lock(queue_mutex);
        done = true;
        queue_cv.notify_one();
    }
private:
    std::string name;
    bool done = false;
    // std::queue<std::unique_ptr<vision::ImageInstance>> queue;
    std::queue<int> queue;
    std::mutex queue_mutex;
    std::condition_variable queue_cv;
    // std::vector<Reception*> receptions;

    void notify(int value) {
        std::cout << "Notified from " << name << ": " << value << std::endl;
    }
};

class Reception
{
public:
    Reception() {};
    Reception(std::string name) : name(name) {};
    void receive();
private:
    std::string name;
};

} // namespace sensory
} // namespace overseer
