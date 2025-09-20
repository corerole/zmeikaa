#pragma once
#ifndef APP_SHADERS
#define APP_SHADERS

#include <algorithm>
#include <vector>
#include <vulkan/vulkan_raii.hpp>

namespace vk {
	namespace supp {
		struct ShaderInstaller {
			private:
				const vk::raii::Device& Device;
			public:
				ShaderInstaller(const vk::raii::Device& Device) : Device(Device) {};
				vk::raii::ShaderModule installShader(const std::vector<unsigned char>& ShaderCode);
		};
	} // ns supp
} // ns vk

#endif // !APP_SHADERS
