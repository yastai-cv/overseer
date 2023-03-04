#pragma once
#include "overseer/sensory/input.hpp"
#include "overseer/sensory/signal.hpp"


namespace overseer
{
namespace sensory
{
class Pathway
{
public:
    Pathway(Input* input, Signal* signal) : input(input), signal(signal) {};

    void process() {
        while (!done) {
            // Wait for a value to be pushed
            int value = input->pull();
            if (value == -1) {
                break;
            }
            // Process the value
            run_tasks(value);
            // Push the value to the signal
            signal->push(value);
        }
    }

    void close() {
        done = true;
    }

private:
    Input* input;
    Signal* signal;
    bool done = false;

    void run_tasks(int value) {
        // Process the value
        std::cout << "Processed input from " << input->get_name() <<": " << value << std::endl;
    }
};
} // namespace sensory
} // namespace overseer