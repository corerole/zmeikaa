#ifndef APP_VK_INSTANCE
#define APP_VK_INSTANCE

#include "../../trash/dbg.h"
#include "../../Window/Window.hpp"
#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include <memory>

struct App_Instance {
	private:
		std::unique_ptr<vk::raii::Instance> Instance;
	public:
		vk::raii::Instance& get();
		App_Instance(vk::raii::Context& context);
};

#endif // !APP_VK_INSTANCE

