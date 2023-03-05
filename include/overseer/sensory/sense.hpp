#pragma once

#include <string>
#include <thread>

#include <overseer/sensory/input.hpp>
#include <overseer/sensory/pathway.hpp>
#include <overseer/sensory/signal.hpp>


namespace overseer
{
namespace sensory
{

// Sense is a collection of Input, Pathway, and Signal.
// It handles the threads for each of the components.
class Sense
{
public:
    Sense(std::string name, Input* input, Pathway* pathway, Signal* signal);
    ~Sense();
    // Open the sense, and start the threads.
    void open();
    // Close the sense, and stop the threads.
    void close();
private:
    std::string name;
    bool running = false;
    // Sense is a collection of Input, Pathway, and Signal
    // Input is responsible for collecting data from the source.
    Input* input;
    // Pathway is responsible for retrieving values from an input
    // processing them, and then pushing them to a signal.
    Pathway* pathway;
    // Signal is responsible for broadcasting the values to the
    // subscribers.
    Signal* signal;
    // Running in threads
    std::thread input_thread;
    std::thread pathway_thread;
    std::thread signal_thread;
};
} // namespace sensory
} // namespace overseer