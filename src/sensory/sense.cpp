#include "overseer/sensory/sense.hpp"


namespace overseer
{
namespace sensory
{
Sense::Sense(std::string name, Input* input, Pathway* pathway, Signal* signal) : name(name), input(input), pathway(pathway), signal(signal) {
    // Sense is a collection of Input, Pathway, and Signal
}

void Sense::open() {
    input_thread = std::thread(&Input::collect, input);
    pathway_thread = std::thread(&Pathway::process, pathway);
    signal_thread = std::thread(&Signal::broadcast, signal);
};

void Sense::close() {
    std::cout << "Closing sense..." << std::endl;
    input->close();
    std::cout << "Closing input..." << std::endl;
    input_thread.join();
    pathway->close();
    std::cout << "Closing pathway..." << std::endl;
    pathway_thread.join();
    signal->close();
    std::cout << "Closing signal..." << std::endl;
    signal_thread.join();
};

} // namespace sensory
} // namespace overseer