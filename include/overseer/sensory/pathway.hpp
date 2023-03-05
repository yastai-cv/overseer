#pragma once

#include <glog/logging.h>

#include "overseer/sensory/input.hpp"
#include "overseer/sensory/signal.hpp"


namespace overseer
{
namespace sensory
{


// The Pathway class is responsible for retrieving values from an input
// passing them through a series of tasks, and then pushing them to a
// the signal queue, for later processing by the subscribers apps.
class Pathway
{
public:
    Pathway(Input* input, Signal* signal);
    ~Pathway();

    // Retrieve the input, process it, and push it to the signal.
    void process();

    // Stop waiting for the next image.
    void close() {
        done = true;
    }

private:
    Input* input;
    Signal* signal;
    bool done = false;

    // Pass the value through the tasks.
    void run_tasks(int value);
};
} // namespace sensory
} // namespace overseer