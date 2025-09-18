#pragma once
#ifndef VKCUBE_UPDATE_FUNCTIONS
#define VKCUBE_UPDATE_FUNCTIONS

#include <chrono>
#include <vulkan/vulkan_raii.hpp>
#include <GLM/glm.hpp>
#include "UBO.hpp"
#include <GLM/ext/matrix_clip_space.hpp>
#include <GLM/ext/matrix_transform.hpp>
#include "../../CommandBuffers/CommandBuffers.hpp"
#include "../Shaders.hpp"

namespace vkcube {
	struct vkCube_CommandBufferData {
		vk::raii::Pipeline& pipeline;
		vk::raii::PipelineLayout& pipelineLayout;
		std::array<vk::DeviceSize, 3> offsets = {};
		std::pair<vk::raii::Buffer&, vk::raii::DeviceMemory&> buffer;
		vk::raii::DescriptorSet& descriptorSet;
		std::chrono::steady_clock::time_point startTime;
	};

	void vkCube_update_UBO(
		vkcube::UBO& ubo,
		const vk::Extent2D& extent,
		std::chrono::steady_clock::time_point startTime
	);

	void vkCube_set_CommandBuffer(
		std::vector<vk::raii::CommandBuffer>& commandBuffers,
		const std::vector<vk::raii::Framebuffer>& framebuffers,
		const vk::raii::RenderPass& renderpass,
		const vk::Rect2D& scissor,
		const vk::Viewport& viewport,
		const void* Data
	);

} // ns vkcube

#endif