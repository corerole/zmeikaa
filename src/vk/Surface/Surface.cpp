#include "Surface.hpp"

namespace vk {
	namespace supp {
		vk::raii::SurfaceKHR get_Surface(GLFWwindow* window, const vk::raii::Instance& instance) {
			VkSurfaceKHR Surface_;
			VkResult res = glfwCreateWindowSurface(*instance, window, nullptr, &Surface_);
			if (res) { std::cout << "Broken Instance! | code: " << res << "\n"; }
			return vk::raii::SurfaceKHR(instance, std::move(Surface_));
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