#ifndef APP_SURFACE
#define APP_SURFACE

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include "../../Window/Window.hpp"
#include <memory>

struct App_Surface {
	private:
		std::unique_ptr<vk::raii::SurfaceKHR> Surface;
	private:
		vk::raii::Instance &Instance;
	public:
		vk::raii::SurfaceKHR& get();
		App_Surface(GLFWwindow* wnd, vk::raii::Instance& Instance_);
};

#endif
