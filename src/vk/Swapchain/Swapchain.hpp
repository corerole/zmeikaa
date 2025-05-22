#ifndef APP_SWAPCHAIN
#define APP_SWAPCHAIN

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include <memory>
#include "../../Window/Window.hpp"
#include "../QueueFamilies/QueueFamilies.hpp"

struct App_Swapchain {
	private:
		std::unique_ptr<vk::raii::SwapchainKHR>			Swapchain;
		vk::SurfaceFormatKHR			SurfaceFormat;
		vk::Extent2D					Extent;
	private:
		vk::raii::PhysicalDevice	&PhysicalDevice;
		vk::raii::SurfaceKHR		&Surface;
		App_Window 					&Wnd;
		vk::raii::Device			&Device;
		App_QueueFamily				&qFamily;
	public:
		// void create_swap_chain();
		// void destroy_SwapChain();
		void update_Swapchain();
	public:
		vk::raii::SwapchainKHR& get();
		vk::SurfaceFormatKHR& get_SurfaceFormatKHR();
		vk::Extent2D& get_Extent2D();
		App_Swapchain(	vk::raii::PhysicalDevice	&PhysicalDevice_,
						vk::raii::SurfaceKHR		&Surface_,
						App_Window					&Wnd_,
						vk::raii::Device			&Device_,
						App_QueueFamily				&qFamily_);
};

#endif // !APP_SWAPCHAIN

