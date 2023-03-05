#include "overseer/sensory/sense.hpp"


namespace overseer
{
namespace sensory
{
Sense::Sense(std::string name, Input* input, Pathway* pathway, Signal* signal) : name(name), input(input), pathway(pathway), signal(signal)
{
    // Sense is a collection of Input, Pathway, and Signal
}

Sense::~Sense()
{
    close();
}

void Sense::open()
{
    running = true;
    input_thread = std::thread(&Input::collect, input);
    pathway_thread = std::thread(&Pathway::process, pathway);
    signal_thread = std::thread(&Signal::broadcast, signal);
};

void Sense::close()
{
    // Make sure the threads are running before closing them.
    if (!running) {
        LOG(WARNING) << "Sense is not running.";
        return;
    }
    running = false;
    LOG(INFO) << "Closing sense...";
    input->close();
    DLOG(INFO) << "Closing input...";
    input_thread.join();
    pathway->close();
    DLOG(INFO) << "Closing pathway...";
    pathway_thread.join();
    signal->close();
    DLOG(INFO) << "Closing signal...";
    signal_thread.join();
};

} // namespace sensory
} // namespace overseer