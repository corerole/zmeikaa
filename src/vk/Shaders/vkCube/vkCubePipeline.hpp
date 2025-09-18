#pragma once
#ifndef VKCUBE_PIPELINE
#define VKCUBE_PIPELINE

#include <vector>
#include <array>
#include <vulkan/vulkan_raii.hpp>
#include "../../PipeLines/PipeLines.hpp"
#include "vkCubeShaderSource.hpp"
#include "../Shaders.hpp"

namespace vkcube {
	vk::raii::DescriptorSetLayout get_DescriptorSetLayout_vkCube(const vk::raii::Device& Device);
	vk::raii::PipelineLayout get_PipelineLayout_vkCube(const vk::raii::Device& Device, const vk::raii::DescriptorSetLayout& descLayout);
	vk::raii::PipelineCache get_PipelineCache_vkCube(const vk::raii::Device& Device);
	vk::raii::Pipeline get_Pipeline_vkCube(
		const vk::raii::Device& Device,
		const vk::raii::RenderPass& RenderPass,
		const vk::Extent2D& Extent,
		const std::vector<vk::raii::ShaderModule>& ShaderModuleHolder,
		const vk::raii::PipelineLayout& pipelineLayout,
		const vk::raii::PipelineCache& pipelineCache
	);
}

#endif