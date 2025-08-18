#include "LogicalQueue.hpp"

#if 0
App_LogicalQueue::App_LogicalQueue(vk::raii::Device& Device, App_QueueFamily& qFamily) {
	// vk::DeviceQueueInfo2 graphicsInfo; 
	// vk::DeviceQueueInfo2 presentInfo;
	GraphicsQueue = std::make_unique<vk::raii::Queue>(Device, qFamily.get_GraphicsFamily(), 0);
	PresentQueue = std::make_unique<vk::raii::Queue>(Device, qFamily.get_PresentFamily(), 0);
}
#endif 