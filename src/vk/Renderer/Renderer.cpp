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

#if 1
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
	// RenderPass
	upRenderpass.reset();
	upRenderpass = std::make_unique<vk::raii::RenderPass>(
		vk::supp::get_RenderPass(
			device,
			surface_format.format
		)
	);
	// vk_PipeLines.update_Pipeline();
	upPipeline.reset();
	upPipeline = std::make_unique<vk::raii::Pipeline>(
		vk::supp::get_PipeLine(
			device,
			StoredVertexID,
			StoredFragmentID,
			extent,
			*upRenderpass,
			pipeline_cache,
			pipeline_layout
		)
	);

	// Framebuffers
	vk::supp::set_SwapchainFramebuffers(
		swapchain_framebuffers,
		device,
		*upRenderpass,
		extent,
		swapchain_imageviews
	);
	// CommandBuffers
	vk::supp::set_CommandBuffers(
		command_buffers,
		swapchain_framebuffers,
		commandpool,
		device,
		*upRenderpass,
		extent,
		*upPipeline,
		VertexBuffer,
		IndexBuffer,
		Indices
	);

	resize_ImagesInFlight();
}
#else
void App_Renderer::update_Swapchain() {};
#endif

#if 1

void App_Renderer::render_frame() {
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
		// update_swap_chain();
		return;
	} else if ((result != vk::Result::eSuccess) && (result != vk::Result::eSuboptimalKHR)) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}
	
	if(ImagesInFlight[imageIndex].getStatus() != vk::Result::eNotReady) {
		VK_CHECK_RESULT(device.waitForFences(*(ImagesInFlight[imageIndex]), VK_TRUE, UINT64_MAX));
	}

	//InFlightFences[CurrentFrame].release();
	ImagesInFlight[imageIndex] = std::move(InFlightFences[CurrentFrame]);
	InFlightFences[CurrentFrame] = std::move(vk::raii::Fence(device, vk::FenceCreateInfo(vk::FenceCreateFlagBits::eSignaled)));

	vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
	vk::Semaphore waitSemaphores[] = { *ImageAvailableSemaphores[CurrentFrame] };
	vk::Semaphore signalSemaphores[] = { *RenderFinishedSemaphores[CurrentFrame] };
	vk::CommandBuffer current[] = { command_buffers[CurrentFrame] };

	vk::SubmitInfo submitInfo(
		waitSemaphores,
		waitStages,
		current,
		signalSemaphores
	);

	device.resetFences(*InFlightFences[CurrentFrame]);

	vk::SubmitInfo submits[] = { submitInfo };
	graphics_queue.submit(submits, InFlightFences[CurrentFrame]);
 
	vk::SwapchainKHR swapChains[] = { *upSwapchain };
	vk::Result some_shit = vk::Result::eSuccess;
	vk::Result result_present_info[] = { some_shit };
	uint32_t image_indices[] = { imageIndex };
	vk::PresentInfoKHR presentInfo(
		signalSemaphores,
		swapChains,
		image_indices,
		result_present_info,
		nullptr
	);
#if 0
	result = PresentQueue.presentKHR(presentInfo);
#else
	auto PQres = present_queue.presentKHR(presentInfo);
#endif

	if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR || (FramebufferResized)) {
		FramebufferResized = false;
		update_Swapchain();
	}

	else if (result != vk::Result::eSuccess) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	CurrentFrame = (CurrentFrame + 1) % (FramesInFlight);
}
#endif