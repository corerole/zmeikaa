#ifndef APP_RENDERPASS
#define APP_RENDERPASS

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <vector>

namespace vk {
	namespace supp {
		vk::raii::RenderPass get_RenderPass(const vk::raii::Device& Device, const vk::Format& SwapchainImageFormat);
	}
}

#if 0
struct App_RenderPass {
	private:
		std::unique_ptr<vk::raii::RenderPass> RenderPass;
	private:
		vk::raii::Device &Device;
		vk::Format &SwapchainImageFormat;
	public:
		void update_RenderPass();

		vk::raii::RenderPass& get_RenderPass() { return *RenderPass; }
		App_RenderPass(vk::raii::Device& Device_, vk::Format& SwapChainImageFormat_);
};
#endif

#endif // !APP_RENDERPASS
