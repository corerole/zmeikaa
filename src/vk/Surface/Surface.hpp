#ifndef APP_SURFACE
#define APP_SURFACE

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include "../../Window/Window.hpp"
#include <memory>

namespace vk {
	namespace supp {
		vk::raii::SurfaceKHR get_Surface(GLFWwindow* window, const vk::raii::Instance& instance);
	}
}

#if 0
struct App_Surface {
	private:
		std::unique_ptr<vk::raii::SurfaceKHR> Surface;
	public:
		vk::raii::SurfaceKHR& get();
		App_Surface(GLFWwindow* wnd, vk::raii::Instance& Instance_);
};
#endif

#endif
