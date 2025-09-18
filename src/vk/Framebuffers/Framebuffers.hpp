#ifndef APP_FRAMEBUFFER
#define	APP_FRAMEBUFFER

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <vector>

namespace vk {
	namespace supp {
		void set_SwapchainFramebuffers(
			std::vector<vk::raii::Framebuffer>& SwapchainFramebuffers,
			const vk::raii::Device& Device,
			const vk::raii::RenderPass& RenderPass,
			const vk::Extent2D& SwapchainExtent,
			const std::vector<vk::raii::ImageView>& SwapchainImageViews,
			const vk::raii::ImageView& DepthImageView
		);
	}
}

#if 0
struct App_Framebuffer {
	private:
		std::vector<vk::raii::Framebuffer>	SwapchainFramebuffers;
	private:
		std::vector<vk::raii::ImageView>	&SwapchainImageViews;
		vk::raii::Device					&Device;
		vk::raii::RenderPass				&RenderPass;
		vk::Extent2D						&SwapchainExtent;
	public:
		void update_framebuffers();
		// void destroy_framebuffers();
		App_Framebuffer(std::vector<vk::raii::ImageView> &SwapchainImageViews_,	vk::raii::Device &LocalDevice_,	vk::raii::RenderPass &RenderPass_, vk::Extent2D &SwapChainExtent_);
		std::vector<vk::raii::Framebuffer>& get_SwapchainFramebuffers() { return SwapchainFramebuffers; }
};
#endif

#endif
