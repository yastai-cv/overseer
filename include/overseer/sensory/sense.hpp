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
class Sense
{
public:
    Sense() {};
    Sense(std::string name) : name(name) {};
    Sense(std::string name, Input* input, Pathway* pathway, Signal* signal);
    void open();
    void close();
private:
    std::string name;
    // Sense is a collection of Input, Pathway, and Signal
    Input* input;
    Pathway* pathway;
    Signal* signal;
    // Running in threads
    std::thread input_thread;
    std::thread pathway_thread;
    std::thread signal_thread;
};
} // namespace sensory
} // namespace overseer