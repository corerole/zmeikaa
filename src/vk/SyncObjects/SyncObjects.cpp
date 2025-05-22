#include "SyncObjects.hpp"

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
	ImagesInFlight.clear();
	vk::FenceCreateInfo fenceInfo{};
	fenceInfo.sType = vk::StructureType::eFenceCreateInfo;
	fenceInfo.flags = vk::FenceCreateFlagBits::eSignaled;
	size_t size = SwapchainImages.size();
	for (size_t i = 0; i < size; ++i) { 
			ImagesInFlight.push_back(std::move(Device.createFence(fenceInfo)));
			ImagesInFlight[i].clear();
	}
}

void App_SyncObjects::update_SyncObjects() {
	ImageAvailableSemaphores.clear();
	RenderFinishedSemaphores.clear();
	InFlightFences.clear();

	vk::SemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = vk::StructureType::eSemaphoreCreateInfo;

	vk::FenceCreateInfo fenceInfo{};
	fenceInfo.sType = vk::StructureType::eFenceCreateInfo;
	fenceInfo.flags = vk::FenceCreateFlagBits::eSignaled;

	resize_ImagesInFlight();
	
	for (uint32_t i = 0; i < FramesInFlight; ++i) {
		ImageAvailableSemaphores.push_back(std::move(Device.createSemaphore(semaphoreInfo)));
		RenderFinishedSemaphores.push_back(std::move(Device.createSemaphore(semaphoreInfo)));
		InFlightFences.push_back(std::move(Device.createFence(fenceInfo)));
	}
}