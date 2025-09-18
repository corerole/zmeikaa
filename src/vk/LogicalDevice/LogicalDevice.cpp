#include "LogicalDevice.hpp"

#if 0
vk::raii::Device& App_LogicalDevice::get() { return *Device; }
#endif

#if 1

namespace vk {
	namespace supp {
		vk::raii::Device get_LogicalDevice(
			const vk::raii::PhysicalDevice& PhysicalDevice,
			const std::pair<uint32_t, uint32_t>& GaP)
		{
			std::set<uint32_t> uniqueQueueFamilies = { GaP.first, GaP.second };
			std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;

			const std::vector<const char*> deviceExtensions = {
				VK_KHR_SWAPCHAIN_EXTENSION_NAME
				// VK_KHR_MAP_MEMORY_2_EXTENSION_NAME
			};

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

			return vk::raii::Device(PhysicalDevice, createInfo);
		}
	}
}
#endif
