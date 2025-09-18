#include "Renderer.hpp"

void App_Renderer::resize_ImagesInFlight() {
	auto& ld = device;
	ImagesInFlight.clear();
	auto create_fence = [&ld]() { return vk::raii::Fence(ld, vk::FenceCreateInfo(vk::FenceCreateFlagBits::eSignaled)); };
	std::generate_n(std::back_inserter(ImagesInFlight), swapchain_images.size(), create_fence);
}

void App_Renderer::update_SyncObjects() {
	ImageAvailableSemaphores.clear();
	RenderFinishedSemaphores.clear();
	InFlightFences.clear();
	auto& ld = device;

	resize_ImagesInFlight();

	auto create_semaphore = [&ld]() { return vk::raii::Semaphore(ld, vk::SemaphoreCreateInfo()); };
	auto create_fence = [&ld]() { return vk::raii::Fence(ld, vk::FenceCreateInfo(vk::FenceCreateFlagBits::eSignaled)); };
	std::generate_n(std::back_inserter(ImageAvailableSemaphores), FramesInFlight, create_semaphore);
	std::generate_n(std::back_inserter(RenderFinishedSemaphores), FramesInFlight, create_semaphore);
	std::generate_n(std::back_inserter(InFlightFences), FramesInFlight, create_fence);
}

void App_Renderer::update_Swapchain() {
	dbgs << "UPDATING SWAPCHAIN" << "\n";
	int width = 0, height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	while (width == 0 || height == 0) {
			glfwGetFramebufferSize(window, &width, &height);
			glfwWaitEvents();
	}
	
	device.waitIdle();

	extent.setHeight(height);
	extent.setWidth(width);
	// vk_Swapchain.update_Swapchain();
	upSwapchain.reset();
	upSwapchain = std::make_unique<vk::raii::SwapchainKHR>(
		vk::supp::get_Swapchain(
			device,
			physical_device,
			surface,
			GaPFQ,
			surface_format,
			extent
		)
	);

	//swapchain images ?
	swapchain_images.clear();
	swapchain_images = (*upSwapchain).getImages();
	//image views
	vk::supp::set_ImageViews(
		device,
		surface_format.format,
		swapchain_images,
		swapchain_imageviews
	);
	// Framebuffers
	vk::supp::set_SwapchainFramebuffers(
		swapchain_framebuffers,
		device,
		renderpass,
		extent,
		swapchain_imageviews,
		depthImageView
	);
	// CommandBuffers
	vk::supp::set_CommandBuffers(
		command_buffers,
		swapchain_framebuffers,
		commandpool,
		device,
		renderpass,
		extent,
		commandBufferData
	);

	resize_ImagesInFlight();
}

void App_Renderer::render_frame() {
	vk::supp::set_CommandBuffers(
		command_buffers,
		swapchain_framebuffers,
		commandpool,
		device,
		renderpass,
		extent,
		commandBufferData
	);

	vk::Fence dwf[] = { *InFlightFences[CurrentFrame] };
	VK_CHECK_RESULT(device.waitForFences(dwf, VK_TRUE, UINT64_MAX));

	unsigned imageIndex = 0;
	vk::AcquireNextImageInfoKHR acquireInfo(
		*upSwapchain,
		UINT64_MAX,
		*ImageAvailableSemaphores[CurrentFrame],
		VK_NULL_HANDLE,
		0x1,
		nullptr
	);

	std::pair<vk::Result, uint32_t> ret = device.acquireNextImage2KHR(acquireInfo);
	vk::Result result = ret.first;
	imageIndex = ret.second;

	if (result == vk::Result::eErrorOutOfDateKHR) {
		update_Swapchain();
		return;
	} else if ((result != vk::Result::eSuccess) && (result != vk::Result::eSuboptimalKHR)) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}
	
	if(ImagesInFlight[imageIndex].getStatus() != vk::Result::eNotReady) {
		VK_CHECK_RESULT(device.waitForFences(*(ImagesInFlight[imageIndex]), VK_TRUE, UINT64_MAX));
	}

#if 1
	ImagesInFlight[imageIndex] = std::move(InFlightFences[CurrentFrame]);
	InFlightFences[CurrentFrame] = std::move(vk::raii::Fence(device, vk::FenceCreateInfo(vk::FenceCreateFlagBits::eSignaled)));
#endif

#if 1
	vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
	vk::Semaphore waitSemaphores[] = { *ImageAvailableSemaphores[CurrentFrame] };
	vk::Semaphore signalSemaphores[] = { *RenderFinishedSemaphores[CurrentFrame] };
	vk::CommandBuffer commandBuffers[] = { command_buffers[CurrentFrame] };

	vk::SubmitInfo submitInfo(
		waitSemaphores,
		waitStages,
		commandBuffers,
		signalSemaphores
	);


	device.resetFences(*InFlightFences[CurrentFrame]);

	vk::SubmitInfo submits[] = { submitInfo };
	graphics_queue.submit(submits, InFlightFences[CurrentFrame]);

#else
	// semaphore, value, stagemask, deviceIndex, pNext;
	vk::SemaphoreSubmitInfo wssi(
		ImageAvailableSemaphores[CurrentFrame],
		0u, 
		vk::PipelineStageFlagBits2::eColorAttachmentOutput,
		0x1u,
		nullptr
	);

	vk::CommandBufferSubmitInfo cbsi(
		command_buffers[CurrentFrame],
		0x1u,
		nullptr
	);

	vk::SemaphoreSubmitInfo sssi(
		RenderFinishedSemaphores[CurrentFrame],
		0u,
		vk::PipelineStageFlagBits2::eColorAttachmentOutput,
		0x1u,
		nullptr
	);

	std::vector<vk::SemaphoreSubmitInfo> waitSemaphoreInfos = { wssi };
	std::vector<vk::CommandBufferSubmitInfo> commandBufferInfos = { cbsi };
	std::vector<vk::SemaphoreSubmitInfo> signalSemaphoreInfos = { sssi };

	vk::SubmitInfo2 submitInfo(
		vk::SubmitFlagBitsKHR::eProtected,
		waitSemaphoreInfos,
		commandBufferInfos,
		signalSemaphoreInfos,
		nullptr
	);

	device.resetFences(*InFlightFences[CurrentFrame]);

	std::vector<vk::SubmitInfo2> submits = { submitInfo };
	graphics_queue.submit2(submits, InFlightFences[CurrentFrame]);
#endif
 
	std::vector<vk::SwapchainKHR> swapChains;
	swapChains.push_back(*upSwapchain);
	std::vector<vk::Result> result_present_info(swapChains.size(), vk::Result::eSuccess);
	// vk::Semaphore signalSemaphores[] = { RenderFinishedSemaphores[CurrentFrame] };
	uint32_t image_indices[] = { imageIndex };
	vk::PresentInfoKHR presentInfo(
		signalSemaphores,
		swapChains,
		image_indices,
		result_present_info,
		nullptr
	);
	result = present_queue.presentKHR(presentInfo);

	for (auto&& x : result_present_info) {
		if (x != vk::Result::eSuccess) {
			dbgs << x << " - PresentInfoKHR return\n";
		}
	}

	if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR || (FramebufferResized)) {
		FramebufferResized = false;
		update_Swapchain();
	} else if (result != vk::Result::eSuccess) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	CurrentFrame = (CurrentFrame + 1) % (FramesInFlight);
}