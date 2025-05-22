#include "CommandPool.hpp"


static std::unique_ptr<vk::raii::CommandPool> create_CommandPool(vk::raii::Device& Device, App_QueueFamily& qFamily) {
	vk::CommandPoolCreateInfo createInfo{};
	createInfo.sType = vk::StructureType::eCommandPoolCreateInfo;
	createInfo.flags = vk::CommandPoolCreateFlags();
	createInfo.queueFamilyIndex = qFamily.get_GraphicsFamily();
	return std::make_unique<vk::raii::CommandPool>(Device, createInfo);
}

void App_CommandPool::update_CommandPool() {
	CommandPool = create_CommandPool(Device, qFamily);
}

App_CommandPool::App_CommandPool(vk::raii::Device	&Device_,
                                App_QueueFamily		&qFamily_) : Device(Device_), qFamily(qFamily_)
{
		update_CommandPool();
    dbgs << "Command Pool Created!\n";
}
