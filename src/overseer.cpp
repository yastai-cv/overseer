#include "overseer/overseer.hpp"


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
    LOG(INFO) << "Loading image...";
    int loaded = this->image.load(image_path);
    if (loaded != 0)
    {
        LOG(FATAL) << "Failed to load image";
        return -1;
    }
    // Check memory
    this->memory->print_memory();

    // Retrieve image
    const cv::Mat imgRef = this->image.get_image();
    LOG(INFO) << "Displaying image...";
    if (imgRef.empty())
    {
        LOG(FATAL) << "Failed to display image";
        return -1;
    }
    // Display image
    // cv::imshow("Image", imgRef);
    // cv::waitKey();

    // Sensory input and pathway
    sensory::Input sensory_input("test input", nullptr);
    sensory::Signal sensory_signal("test signal");
    sensory::Pathway sensory_pathway(&sensory_input, &sensory_signal);
    sensory::Sense sense("test sense", &sensory_input, &sensory_pathway, &sensory_signal);

    sense.open();
    // wait for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
    sense.close();

    return 0;
}
} // namespace overseer