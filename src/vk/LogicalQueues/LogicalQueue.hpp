#ifndef MY_LOGICALQUEUE
#define MY_LOGICALQUEUE

#include "../QueueFamilies/QueueFamilies.hpp"
#include <vulkan/vulkan_raii.hpp>
#include <memory>

struct App_LogicalQueue {
	private:
		std::unique_ptr<vk::raii::Queue> PresentQueue;
		std::unique_ptr<vk::raii::Queue> GraphicsQueue;
	public:
		vk::raii::Queue& getGraphicsQueue() { return *GraphicsQueue; }
		vk::raii::Queue& getPresentQueue() { return *PresentQueue; }
		App_LogicalQueue(vk::raii::Device& Device, App_QueueFamily& qFamily);
};

#endif