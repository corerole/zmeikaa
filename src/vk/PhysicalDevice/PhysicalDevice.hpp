#ifndef APP_PHYSDEVICE
#define APP_PHYSDEVICE

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include <memory>

struct App_PhysicalDevice {
	private: 
		std::unique_ptr<vk::raii::PhysicalDevice> PhysicalDevice;
	private:
		vk::raii::Instance& Instance;
	public:
		vk::raii::PhysicalDevice& get();
		App_PhysicalDevice(vk::raii::Instance& Instance);
};

#endif // !APP_PHYSDEVICE

