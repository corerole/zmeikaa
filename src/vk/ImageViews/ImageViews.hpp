#ifndef APP_IMAGEVIEWS
#define APP_IMAGEVIEWS

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <vector>

struct App_ImageViews {
	private:
		std::vector<vk::raii::ImageView> SwapchainImageViews;
		std::vector<vk::Image> SwapchainImages;
		vk::Extent2D SwapchainExtent;
		vk::Format SwapchainImageFormat;
	private:
		vk::raii::Device &Device;
		vk::raii::SwapchainKHR &Swapchain;
		vk::SurfaceFormatKHR &SurfaceFormat;
		vk::Extent2D &Extent;
	public:
		std::vector<vk::raii::ImageView> &get_SwapchainImageViews() { return SwapchainImageViews;}
		vk::Format&	get_SwapchainImageFormat() { return SwapchainImageFormat; }
		std::vector<vk::Image>&	get_SwapchainImages() { return SwapchainImages; }
		vk::Extent2D& get_SwapchainExtent() { return SwapchainExtent; }
	private:
		void update_SwapchainImages();
		void update_ImageViews();
	public:
		void update();
		// void destroy_SwapChainImageViews();
	public:
		App_ImageViews(vk::raii::Device& Device_, vk::raii::SwapchainKHR& Swapchain_, vk::SurfaceFormatKHR& SurfaceFormat_, vk::Extent2D& Extent_);
};

#endif // !APP_IMAGEVIEWS