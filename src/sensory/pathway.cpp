#include "overseer/sensory/pathway.hpp"

namespace overseer
{
namespace sensory
{

Pathway::Pathway(Input* input, Signal* signal) : input(input), signal(signal) {};

Pathway::~Pathway() {
    close();
}

void Pathway::process()
{
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

void Pathway::run_tasks(int value)
{
    // Process the value
    std::cout << "Processed input from " << input->get_name() <<": " << value << std::endl;
}

} // namespace sensory
} // namespace overseer