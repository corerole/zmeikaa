#ifndef APP_COMMANDPOOL
#define APP_COMMANDPOOL

#include <vulkan/vulkan_raii.hpp>
#include "../../trash/dbg.h"
#include <memory>
#include "../QueueFamilies/QueueFamilies.hpp"

struct App_CommandPool {
	private:
		std::unique_ptr<vk::raii::CommandPool> CommandPool;
	private:
		vk::raii::Device	&Device;
		App_QueueFamily		&qFamily;
	public:
		void update_CommandPool();
	public:
		vk::raii::CommandPool& get() { return *CommandPool; }
		App_CommandPool(vk::raii::Device &Device_, App_QueueFamily& qFamily_);
};

#endif // !APP_COMMANDPOOL

