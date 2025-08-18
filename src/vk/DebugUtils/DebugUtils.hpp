#ifndef MY_DEBUGUTILS
#define MY_DEBUGUTILS

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <vulkan/vulkan.h>
#include <memory>


namespace vk {
	namespace supp {
		vk::raii::DebugUtilsMessengerEXT get_DebugUtils(const vk::raii::Instance& instance);
	}
}

#if 0

struct DebugUserData {};

struct App_DebugUtils {
	private:
		vk::raii::Instance& Instance;
	private:
		void* userdata;
		vk::raii::DebugUtilsMessengerEXT messenger;
	public:
		App_DebugUtils(vk::raii::Instance& Instance_);
		vk::raii::DebugUtilsMessengerEXT& get() { return messenger; };
		const vk::raii::DebugUtilsMessengerEXT& get() const { return messenger; };
};

#endif

#endif