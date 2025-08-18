#ifndef APP_PHYSDEVICE
#define APP_PHYSDEVICE

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include <memory>

namespace vk {
	namespace supp {
		vk::raii::PhysicalDevice get_PhysicalDevice(const vk::raii::Instance& instance);
	}
}

#if 0
struct App_PhysicalDevice {
	private: 
		std::unique_ptr<vk::raii::PhysicalDevice> PhysicalDevice;
	public:
		vk::raii::PhysicalDevice& get();
		App_PhysicalDevice(vk::raii::Instance& Instance);
};
#endif

#endif // !APP_PHYSDEVICE

