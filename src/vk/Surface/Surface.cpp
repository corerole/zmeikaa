#include "Surface.hpp"

namespace vk {
	namespace supp {
		vk::raii::SurfaceKHR get_Surface(GLFWwindow* window, const vk::raii::Instance& instance) {
#if 1
			VkSurfaceKHR Surface_;
			VkResult res = glfwCreateWindowSurface(*instance, window, nullptr, &Surface_);
			if (res) { throw vulkan_error(static_cast<vk::Result>(res), "Can not create vk::SurfaceKHR ! | code: "); }
			return vk::raii::SurfaceKHR(instance, std::move(Surface_));
#else
			vk::DisplaySurfaceCreateFlagsKHR flag; // = vk::DisplaySurfaceCreateFlagBitsKHR:: /* empty */;
			vk::DisplayModeKHR displayMode;
			uint32_t planeIndex = 0u;
			uint32_t planeStackIndex = 0u;
			vk::SurfaceTransformFlagBitsKHR transform = vk::SurfaceTransformFlagBitsKHR::eIdentity;
			float globalAlpha = 0.0f;
			vk::DisplayPlaneAlphaFlagBitsKHR alphaMode = vk::DisplayPlaneAlphaFlagBitsKHR::eOpaque;
			vk::Extent2D imageExtent(0u, 0u);

			vk::DisplaySurfaceCreateInfoKHR createInfo(
				flag,
				displayMode,
				planeIndex,
				planeStackIndex,
				transform,
				globalAlpha,
				alphaMode,
				imageExtent
			);

			return vk::raii::SurfaceKHR(instance, createInfo);
#endif
		}
	}
}

#if 0
vk::raii::SurfaceKHR& App_Surface::get() { return *Surface; }

App_Surface::App_Surface(GLFWwindow* window, vk::raii::Instance& Instance) {
	VkSurfaceKHR Surface_;
	VkResult res = glfwCreateWindowSurface(*Instance, window, nullptr, &Surface_);
	if (res) { std::cout << "Broken Instance! | code: " << res << "\n"; }
	Surface = std::make_unique<vk::raii::SurfaceKHR>(Instance, std::move(Surface_));
}
#endif