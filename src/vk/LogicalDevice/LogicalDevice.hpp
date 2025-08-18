#ifndef APP_LOGICALDEVICE
#define APP_LOGICALDEVICE

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include <memory>
#include "../QueueFamilies/QueueFamilies.hpp"
#include <set>

namespace vk {
	namespace supp {
		vk::raii::Device get_LogicalDevice(const vk::raii::PhysicalDevice&, const std::pair<uint32_t, uint32_t>&);
	}
}

#if 0
struct App_LogicalDevice {
	private:
		std::unique_ptr<vk::raii::Device> Device;
	private:
		vk::raii::PhysicalDevice	&PhysicalDevice;
		App_QueueFamily						&qfamily;
	public:
		App_LogicalDevice(vk::raii::PhysicalDevice& PhysicalDevice_, App_QueueFamily& qfamily_);
		vk::raii::Device& get();
};
#endif

#endif