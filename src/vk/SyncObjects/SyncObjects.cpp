#include "SyncObjects.hpp"

#if 0

App_SyncObjects::App_SyncObjects(std::vector<vk::Image> &SwapchainImages_,
								vk::raii::Device &Device_,
								uint32_t FramesInFlight_)
								:
								SwapchainImages(SwapchainImages_),
								Device(Device_),
								FramesInFlight(FramesInFlight_)
{
	update_SyncObjects();
}

void App_SyncObjects::resize_ImagesInFlight() {
	auto& ld = Device;
	ImagesInFlight.clear();
	auto create_fence = [&ld]() { return vk::raii::Fence(ld, vk::FenceCreateInfo(vk::FenceCreateFlagBits::eSignaled)); };
	std::generate_n(std::back_inserter(ImagesInFlight), SwapchainImages.size(), create_fence);
}

void App_SyncObjects::update_SyncObjects() {
	ImageAvailableSemaphores.clear();
	RenderFinishedSemaphores.clear();
	InFlightFences.clear();
	auto& ld = Device;

	resize_ImagesInFlight();

	auto create_semaphore = [&ld](){ return vk::raii::Semaphore(ld, vk::SemaphoreCreateInfo()); };
	auto create_fence = [&ld](){ return vk::raii::Fence(ld, vk::FenceCreateInfo(vk::FenceCreateFlagBits::eSignaled)); };
	std::generate_n(std::back_inserter(ImageAvailableSemaphores), FramesInFlight, create_semaphore);
	std::generate_n(std::back_inserter(RenderFinishedSemaphores), FramesInFlight, create_semaphore);
	std::generate_n(std::back_inserter(InFlightFences), FramesInFlight, create_fence);
}

#endif