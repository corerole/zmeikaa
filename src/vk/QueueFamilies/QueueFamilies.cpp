#include "QueueFamilies.hpp"

App_QueueFamily::App_QueueFamily(vk::raii::PhysicalDevice& PhysicalDevice_,
                                vk::raii::SurfaceKHR& Surface_) : PhysicalDevice(PhysicalDevice_), Surface(Surface_)
{
    std::vector<vk::QueueFamilyProperties> queueFamilies = PhysicalDevice.getQueueFamilyProperties();

    uint32_t i = 0;
    dbgs << (queueFamilies.size()) << " queue families found\n";

    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
            GraphicsQueueFamily.val = i;
            dbgs << "Graphics queue family: " << i << std::endl;
        }

        VkBool32 presentSupport = PhysicalDevice.getSurfaceSupportKHR(i, Surface);

        if (presentSupport) {
            PresentQueueFamily.val = i;
            dbgs << "Present queue family: " << i << std::endl;
        }


        if (((PresentQueueFamily.val) != UINT_MAX) && ((GraphicsQueueFamily.val) != UINT_MAX)) { //
            break;
        }

        i += 1;
    }

    if (((PresentQueueFamily.val) == UINT_MAX) || ((GraphicsQueueFamily.val) == UINT_MAX))
        throw std::runtime_error("Present and Graphics not found");
}