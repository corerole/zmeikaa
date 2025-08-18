#include "Framebuffers.hpp"

#if 0
App_Framebuffer::App_Framebuffer(std::vector<vk::raii::ImageView>& SwapchainImageViews_,
								 vk::raii::Device				&Device_,
								 vk::raii::RenderPass   &RenderPass_,
								 vk::Extent2D						&SwapchainExtent_) : 
								 SwapchainImageViews(SwapchainImageViews_),
								 Device(Device_),
								 RenderPass(RenderPass_),
								 SwapchainExtent(SwapchainExtent_)
{
	update_framebuffers();
	dbgs << "FrameBuffers Created!\n";
}
#endif

namespace vk {
	namespace supp {
		void set_SwapchainFramebuffers(
			std::vector<vk::raii::Framebuffer>& SwapchainFramebuffers,
			const vk::raii::Device& Device,
			const vk::raii::RenderPass& RenderPass,
			const vk::Extent2D& SwapchainExtent,
			const std::vector<vk::raii::ImageView>& SwapchainImageViews
		) {
			SwapchainFramebuffers.clear();
			unsigned nFrameBuffers = (unsigned)SwapchainImageViews.size();
			dbgs << "Initializing " << nFrameBuffers << " frame buffers\n";
			for (size_t i = 0; i < nFrameBuffers; i++) {
				vk::FramebufferCreateInfo framebufferInfo{};
				framebufferInfo.sType = vk::StructureType::eFramebufferCreateInfo;
				framebufferInfo.renderPass = RenderPass;
				framebufferInfo.attachmentCount = 1;
				framebufferInfo.pAttachments = &(*(SwapchainImageViews[i]));
				framebufferInfo.width = SwapchainExtent.width;
				framebufferInfo.height = SwapchainExtent.height;
				framebufferInfo.layers = 1;
				SwapchainFramebuffers.emplace_back(Device, framebufferInfo);
			}
		}
	}
}