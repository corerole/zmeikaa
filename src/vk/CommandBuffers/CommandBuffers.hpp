#pragma once
#ifndef APP_COMMANDBUFFERS
#define APP_COMMANDBUFFERS

#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include "../../trash/dbg.h"
#include "../Shaders/Shaders.hpp"

namespace vk {
	namespace supp {

		using commandBufferUpdateFunc = void (*)(
			std::vector<vk::raii::CommandBuffer>& commandBuffers,
			const std::vector<vk::raii::Framebuffer>& framebuffers,
			const vk::raii::RenderPass& renderpass,
			const vk::Rect2D& scissor,
			const vk::Viewport& viewport,
			const void* data
		);

		struct CommandBufferData {
			void* data = nullptr;
			commandBufferUpdateFunc f;
		};

		void set_CommandBuffers(
			std::vector<vk::raii::CommandBuffer>& CommandBuffers,
			const std::vector<vk::raii::Framebuffer>& SwapchainFramebuffers,
			const vk::raii::CommandPool& CommandPool,
			const vk::raii::Device& Device,
			const vk::raii::RenderPass& RenderPass,
			const vk::Extent2D& SwapchainExtent,
			const std::vector<vk::supp::CommandBufferData>& CommandBufferData
		);
	}
}

#endif
