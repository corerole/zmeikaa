#include "Framebuffers.hpp"

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

void App_Framebuffer::update_framebuffers() {
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
		SwapchainFramebuffers.push_back(vk::raii::Framebuffer(Device, framebufferInfo));
	}
}
