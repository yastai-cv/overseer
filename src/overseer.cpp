#include <iostream>
#include <opencv2/opencv.hpp>
#include "overseer/overseer.hpp"
#include "overseer/vision/image.hpp"
#include "overseer/vision/visual_memory.hpp"
#include "overseer/sensory/input.hpp"
#include "overseer/sensory/pathway.hpp"


namespace overseer
{
Overseer::Overseer()
{
    this->memory = std::make_shared<vision::VisualMemory>();
    this->image = vision::ImageInstance(this->memory);
}

int Overseer::run(const char *image_path)
{
    // Load image
    std::cout << "Loading image..." << std::endl;
    int loaded = this->image.load(image_path);
    if (loaded != 0)
    {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }
    // Check memory
    this->memory->print_memory();

    // Retrieve image
    const cv::Mat imgRef = this->image.get_image();
    std::cout << "Displaying image..." << std::endl;
    if (imgRef.empty())
    {
        std::cerr << "Failed to display image" << std::endl;
        return -1;
    }
    // Display image
    // cv::imshow("Image", imgRef);
    // cv::waitKey();

    // Sensory input and pathway
    // TODO: Rename to Input and Pathway
    sensory::SensoryInput sensory_input("test", nullptr);
    sensory::SensoryPathway sensory_pathway(&sensory_input);

    std::thread input_thread(&sensory::SensoryInput::collect, &sensory_input);
    std::thread pathway_thread(&sensory::SensoryPathway::process, &sensory_pathway);
    
    input_thread.join();
    pathway_thread.join();

    return 0;
}
} // namespace overseer