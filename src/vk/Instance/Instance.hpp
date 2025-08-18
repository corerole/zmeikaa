#ifndef APP_VK_INSTANCE
#define APP_VK_INSTANCE

#include "../../trash/dbg.h"
#include "../../Window/Window.hpp"
#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include <memory>

namespace vk {
	namespace supp {
		vk::raii::Instance get_Instance(const vk::raii::Context& context);
	}
}

#if 0

struct App_Instance {
	private:
		std::vector<const char*> extensions;
		std::vector<const char*> layers;
		vk::ApplicationInfo appInfo;
		vk::InstanceCreateInfo createInfo;
		std::unique_ptr<vk::raii::Instance> Instance;
	public:
		vk::raii::Instance& get();
		App_Instance(vk::raii::Context& context);
};

#endif

#endif // !APP_VK_INSTANCE

