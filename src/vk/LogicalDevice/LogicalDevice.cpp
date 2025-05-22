#include "LogicalDevice.hpp"

vk::raii::Device& App_LogicalDevice::get() { return *Device; }

#if 1
App_LogicalDevice::App_LogicalDevice(vk::raii::PhysicalDevice& PhysicalDevice_, App_QueueFamily& qfamily_) : PhysicalDevice(PhysicalDevice_), qfamily(qfamily_)
{
    std::set<uint32_t> uniqueQueueFamilies = { qfamily.get_PresentFamily(), qfamily.get_GraphicsFamily() };
    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;

    const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    float queuePriority = 1.0f;
    for (auto queueFamily : uniqueQueueFamilies) {
        vk::DeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
        queueCreateInfo.flags = vk::DeviceQueueCreateFlags();
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    // note: we are querying no device features
    vk::PhysicalDeviceFeatures deviceFeatures{};

    dbgs << deviceExtensions.size() << " device extensions to enable\n";
    vk::DeviceCreateInfo createInfo{};
    createInfo.sType = vk::StructureType::eDeviceCreateInfo;
    createInfo.flags = vk::DeviceCreateFlags();
    createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    Device = std::make_unique<vk::raii::Device>(PhysicalDevice, createInfo);
}
#endif
