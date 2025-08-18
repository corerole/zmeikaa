#include "CommandPool.hpp"

namespace vk {
	namespace supp {
		vk::raii::CommandPool get_CommandPool(
			const vk::raii::Device& Device,
			const std::pair<uint32_t, uint32_t>& GaP
		) {
			vk::CommandPoolCreateInfo createInfo{};
			createInfo.sType = vk::StructureType::eCommandPoolCreateInfo;
			createInfo.flags = vk::CommandPoolCreateFlags();
			createInfo.queueFamilyIndex = GaP.first;
			return vk::raii::CommandPool(Device, createInfo);
		}
	}
}

#if 0
void App_CommandPool::update_CommandPool() {
	CommandPool = create_CommandPool(Device, qFamily);
}

App_CommandPool::App_CommandPool(vk::raii::Device	&Device_,
                                App_QueueFamily		&qFamily_) : Device(Device_), qFamily(qFamily_)
{
		update_CommandPool();
    dbgs << "Command Pool Created!\n";
}
#endif