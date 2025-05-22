#include "PhysicalDevice.hpp"

App_PhysicalDevice::App_PhysicalDevice(vk::raii::Instance& Instance_) : Instance(Instance_) {
    std::vector<vk::raii::PhysicalDevice> PhysicalDevices = Instance.enumeratePhysicalDevices();
#if 0
    unsigned deviceCount = 0;
    VK_CHECK_RESULT(vkEnumeratePhysicalDevices(*Instance, &deviceCount, nullptr));

    if (deviceCount != 1) {
        throw std::runtime_error("Multiple Vulkan devices not supported yet");
    }
    dbgs << "devices enumerated: " << deviceCount << "\n";


    VK_CHECK_RESULT(vkEnumeratePhysicalDevices(*Instance, &deviceCount, &PhysDevice));
    dbgs << "Phys Device Captured!\n";
#endif
    dbgs << "devices enumerated: " << (PhysicalDevices.size()) << "\n";
    PhysicalDevice = std::make_unique<vk::raii::PhysicalDevice>(std::move(PhysicalDevices[0]));
}

vk::raii::PhysicalDevice& App_PhysicalDevice::get() { return *PhysicalDevice; }