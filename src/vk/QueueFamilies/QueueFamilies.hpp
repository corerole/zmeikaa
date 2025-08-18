#ifndef APP_QUEUEFAMILY
#define APP_QUEUEFAMILY

#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include "../../trash/dbg.h"
#include <stdexcept>
#include <utility>

namespace vk {
	namespace supp {
		std::pair<uint32_t, uint32_t> get_QueueFamilies(const vk::raii::PhysicalDevice&, const vk::raii::SurfaceKHR&);
	}
}


#if 0

struct GraphicsQueueFamily {
	uint32_t val = UINT_MAX;
};

struct PresentQueueFamily {
	uint32_t val = UINT_MAX;
};

struct App_QueueFamily {
	private:
		GraphicsQueueFamily GraphicsQueueFamily;
		PresentQueueFamily  PresentQueueFamily;
	private:
		vk::raii::PhysicalDevice&	PhysicalDevice;
		vk::raii::SurfaceKHR& Surface;
	public:
		uint32_t& get_GraphicsFamily() { return GraphicsQueueFamily.val; }
		uint32_t& get_PresentFamily() { return PresentQueueFamily.val; }
		App_QueueFamily(vk::raii::PhysicalDevice& PhysDevice_, vk::raii::SurfaceKHR& Surface_);
};

#endif

#endif
