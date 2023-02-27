#pragma once
#include "overseer/sensory/input.hpp"


namespace overseer
{
namespace sensory
{
class SensoryPathway
{
public:
    SensoryPathway(SensoryInput* input) : input(input) {}

    void process() {
        while (true) {
            int value = input->next();
            if (value == -1) {
                break;
            }
            std::cout << "Processed: " << value << std::endl;
        }
    }
private:
    SensoryInput* input;
};
} // namespace sensory
} // namespace overseer