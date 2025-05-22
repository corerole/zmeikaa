#ifndef APP_SYNCOBJECTS
#define APP_SYNCOBJECTS

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <vector>

struct App_SyncObjects {
	private:
		std::vector<vk::raii::Semaphore>	ImageAvailableSemaphores;
		std::vector<vk::raii::Semaphore>	RenderFinishedSemaphores;
		std::vector<vk::raii::Fence>		InFlightFences;
		std::vector<vk::raii::Fence>		ImagesInFlight;
	private:
		std::vector<vk::Image>		&SwapchainImages;
		vk::raii::Device					&Device;
		uint32_t									FramesInFlight;
	public:
		void update_SyncObjects();
		void resize_ImagesInFlight();
	public:
		App_SyncObjects(std::vector<vk::Image> &SwapChainImages_,	vk::raii::Device &Device_, uint32_t FramesInFlight_);
		std::vector<vk::raii::Semaphore>& get_ImageAvailableSemaphores() { return ImageAvailableSemaphores; }
		std::vector<vk::raii::Semaphore>& get_RenderFinishedSemaphores() { return RenderFinishedSemaphores; }
		std::vector<vk::raii::Fence>& get_InFlightFences() { return InFlightFences; }
		std::vector<vk::raii::Fence>& get_ImagesInFlight() { return ImagesInFlight; }
};

#endif
