#include "Renderer.hpp"

#if 0
 void App_Renderer::render_frame() {};
#else
void App_Renderer::create_swap_chain() {
		// vk_Buffers.create_buffers(); // my
		vk_Swapchain.update_Swapchain();
		vk_ImageViews.update();
		vk_RenderPass.update_RenderPass();
		vk_PipeLines.update_Pipeline();
		vk_Framebuffer.update_framebuffers();
		vk_CommandBuffers.update_CommandBuffers();
}

void App_Renderer::update_swap_chain() {
	int width = 0, height = 0;
	glfwGetFramebufferSize(Window.get(), &width, &height);
	while (width == 0 || height == 0) {
			glfwGetFramebufferSize(Window.get(), &width, &height);
			glfwWaitEvents();
	}
	
	vk_LogicalDevice.get().waitIdle();
 
	create_swap_chain();
#if 0
	vk_SyncObjects.get_ImagesInFlight().resize(
			vk_ImageViews.get_SwapchainImages().size(),
			vk_LogicalDevice.get().createFence(
				vk::FenceCreateInfo(vk::FenceCreateFlagBits::eSignaled)
			)
	);
#endif
	vk_SyncObjects.resize_ImagesInFlight();
}

void App_Renderer::render_frame() {
	vk::raii::Device& Device = vk_LogicalDevice.get();
	vk::raii::Queue& GraphicsQueue = vk_LogicalQueues.getGraphicsQueue();
	vk::raii::Queue& PresentQueue = vk_LogicalQueues.getPresentQueue();
	std::vector<vk::raii::Fence>& ImagesInFlight = vk_SyncObjects.get_ImagesInFlight();
	std::vector<vk::raii::Fence>& InFlightFences = vk_SyncObjects.get_InFlightFences();
	std::vector<vk::raii::Semaphore>& ImageAvailableSemaphores = vk_SyncObjects.get_ImageAvailableSemaphores();
	std::vector<vk::raii::Semaphore>& RenderFinishedSemaphores = vk_SyncObjects.get_RenderFinishedSemaphores();
	
	vk::Result res = Device.waitForFences(*InFlightFences[CurrentFrame], VK_TRUE, UINT64_MAX);
	VK_CHECK_RESULT(res);

	vk::AcquireNextImageInfoKHR acquireInfo{};
	acquireInfo.sType = vk::StructureType::eAcquireNextImageInfoKHR;
	acquireInfo.swapchain = vk_Swapchain.get();
	acquireInfo.timeout = UINT64_MAX;
	acquireInfo.semaphore = ImageAvailableSemaphores[CurrentFrame];
	acquireInfo.fence = VK_NULL_HANDLE;
	acquireInfo.deviceMask = 0;

	vk::Result result;
	unsigned imageIndex = 0;
	bool vk_ver = false;
	if(vk_ver) {
		std::pair<vk::Result, uint32_t> ret = Device.acquireNextImage2KHR(acquireInfo);
		vk::Result result = ret.first;
		unsigned imageIndex = ret.second;
	}	else {
		auto result_ = vkAcquireNextImageKHR(*Device, *(vk_Swapchain.get()), UINT64_MAX, *ImageAvailableSemaphores[CurrentFrame], VK_NULL_HANDLE, &imageIndex);
		result = vk::Result(result_);
		VK_CHECK_RESULT(result);
	}

	if (result == vk::Result::eErrorOutOfDateKHR) {
		update_swap_chain();
		return;
	} else if ((result != vk::Result::eSuccess) && (result != vk::Result::eSuboptimalKHR)) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}
	
	if((&(ImagesInFlight[imageIndex])) != VK_NULL_HANDLE) {
		vk::Result res = Device.waitForFences(*ImagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
		VK_CHECK_RESULT(res);
	}

#if 0
	size_t size = sizeof(vk::raii::Fence);
	void* dest = new char[size];
	void* src = (&(InFlightFences[CurrentFrame]));
	std::memcpy(dest, src, size);
	ImagesInFlight[imageIndex] = std::move((*((vk::raii::Fence*)dest)));
	 
	InFlightFences[CurrentFrame].release();
#endif
	

	vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
	vk::Semaphore waitSemaphores[] = { ImageAvailableSemaphores[CurrentFrame] };
	vk::Semaphore signalSemaphores[] = { RenderFinishedSemaphores[CurrentFrame] };

	vk::SubmitInfo submitInfo{};
	submitInfo.sType = vk::StructureType::eSubmitInfo;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &(*((vk_CommandBuffers.get_CommandBuffers())[imageIndex]));
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	GraphicsQueue.submit(submitInfo, InFlightFences[CurrentFrame]);
 
	vk::SwapchainKHR swapChains[] = { vk_Swapchain.get() };
	vk::PresentInfoKHR presentInfo{};
	presentInfo.sType = vk::StructureType::ePresentInfoKHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;

	result = PresentQueue.presentKHR(presentInfo);

	if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR || (*FramebufferResized)) {
		*FramebufferResized = false;
		update_swap_chain();
	}

	else if (result != vk::Result::eSuccess) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	CurrentFrame = (CurrentFrame + 1) % (*FramesInFlight);
	dbgs << "Frame Renderd\n";
}
#endif