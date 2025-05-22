#ifndef MY_DEBUGUTILS
#define MY_DEBUGUTILS

#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <memory>

struct DebugUserData {};

struct App_DebugUtils {
	private:
		std::unique_ptr<vk::raii::DebugUtilsMessengerEXT> messenger;
		DebugUserData userdata;
	private:
		vk::raii::Instance& Instance;
	public:
		App_DebugUtils(vk::raii::Instance& Instance_);
		vk::raii::DebugUtilsMessengerEXT& get() { return *messenger; };
};

#endif