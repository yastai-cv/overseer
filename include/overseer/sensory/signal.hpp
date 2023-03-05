#pragma once

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>

#include <glog/logging.h>


namespace overseer
{
namespace sensory
{

// Signal is a queue of values that can be pushed to by a pathway, and
// broadcast to subscribers.
class Signal
{
public:
    Signal(std::string name);
    ~Signal();

    // Push a value to the queue
    void push(int value);

    // Broadcast the values to the subscribers
    void broadcast();

    // Add a subscriber
    void subscribe();

    // Remove a subscriber
    void unsubscribe();

    // Stop waiting for the next value.
    void close();
private:
    // The name of the signal
    std::string name;
    // Subscribers to the signal
    // std::vector<Reception*> receptions;
    // Whether the signal is closed
    bool done = false;
    // The queue of values
    std::queue<int> queue;
    // std::queue<std::unique_ptr<vision::ImageInstance>> queue;
    
    // Control access to the queue.
    std::mutex queue_mutex;
    std::condition_variable queue_cv;

    // Pass the value to the subscribers
    void notify(int value);
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
