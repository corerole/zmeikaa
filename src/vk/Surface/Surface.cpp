#include "Surface.hpp"

vk::raii::SurfaceKHR& App_Surface::get() { return *Surface; }

App_Surface::App_Surface(GLFWwindow* window, vk::raii::Instance& Instance_) : Instance(Instance_) {
	VkSurfaceKHR Surface_;
	VkResult res = glfwCreateWindowSurface(*Instance, window, nullptr, &Surface_);
	if (res) { std::cout << "Broken Instance! | code: " << res << "\n"; }
	Surface = std::make_unique<vk::raii::SurfaceKHR>(Instance, std::move(Surface_));
}