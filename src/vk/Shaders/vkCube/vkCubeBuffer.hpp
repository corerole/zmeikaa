#pragma once
#ifndef VKCUBE_BUFFER
#define VKCUBE_BUFFER

#include <vulkan/vulkan.hpp>
#include "vkCubeShaderData.hpp"
#include "UBO.hpp"
#include "../../Buffers/Buffers.hpp"

namespace vkcube {
	std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_Buffers_vkCube(vk::supp::BufferCreater& bc);
}

#endif