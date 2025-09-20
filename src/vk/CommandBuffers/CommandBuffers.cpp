#include "CommandBuffers.hpp"

#if 1
namespace {
	vk::Viewport get_Viewport(vk::Extent2D extent, unsigned t_width, unsigned t_height) {
		const float target_aspect = static_cast<float>(t_width) / static_cast<float>(t_height);
		const float current_aspect = static_cast<float>(extent.width) / static_cast<float>(extent.height);
		float x = 0.0f;
		float y = 0.0f;
		float width = static_cast<float>(extent.width);
		float height = static_cast<float>(extent.height);

		if (current_aspect > target_aspect) {
			width = height * target_aspect;
			x = (static_cast<float>(extent.width) - width) * 0.5f;
		}	else {
			height = width / target_aspect;
			y = (static_cast<float>(extent.height) - height) * 0.5f;
		}
		return vk::Viewport(x, y + height, width, -height, 0.0f, 1.0f);
	}
} // anon ns
#else
namespace {
	vk::Viewport get_Viewport(vk::Extent2D extent, unsigned t_width, unsigned t_height) {
		const float target_aspect = static_cast<float>(t_width) / static_cast<float>(t_height);
		const float current_aspect = static_cast<float>(extent.width) / static_cast<float>(extent.height);
		float x = 0.0f;
		float y = 0.0f;
		float width = static_cast<float>(extent.width);
		float height = static_cast<float>(extent.height);

		if (current_aspect > target_aspect) {
			width = height * target_aspect;
			x = (static_cast<float>(extent.width) - width) * 0.5f;
		}	else {
			height = width / target_aspect;
			y = (static_cast<float>(extent.height) - height) * 0.5f;
		}
		return vk::Viewport(x, y, width, height, 0.0f, 1.0f);
	}
} // anon ns
#endif

#if 0
void App_CommandBuffers::update_CommandBuffers() {
#endif
namespace vk {
	namespace supp {
		void set_CommandBuffers(
			std::vector<vk::raii::CommandBuffer>& commandBuffers,
			const std::vector<vk::raii::Framebuffer>& framebuffers,
			const vk::raii::CommandPool& CommandPool,
			const vk::raii::Device& Device,
			const vk::raii::RenderPass& RenderPass,
			const vk::Extent2D& extent,
			const std::vector<vk::supp::CommandBufferData>& commandBufferData
		) {
			commandBuffers.clear();
			unsigned NFrameBufs = (unsigned)framebuffers.size();
			// dbgs << "Number of command buffers: " << NFrameBufs << std::endl;

			vk::CommandBufferAllocateInfo allocInfo{};
			allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
			allocInfo.commandPool = CommandPool;
			allocInfo.level = vk::CommandBufferLevel::ePrimary;
			allocInfo.commandBufferCount = NFrameBufs;

			// dbgs << "Height :" <<  extent.height << "| Width: " << extent.width << std::endl;
			commandBuffers = Device.allocateCommandBuffers(allocInfo);
			auto viewport = get_Viewport(extent, 16, 9);

			// dbgs << "H: " << viewport.height << "| W:" << viewport.width << " | x:" << viewport.x << " | y: " << viewport.y << std::endl;

#if 0
			vk::Rect2D scissor{};
			scissor.offset = vk::Offset2D(static_cast<int32_t>(viewport.x), static_cast<int32_t>(viewport.y));
			scissor.extent = vk::Extent2D(static_cast<uint32_t>(viewport.width), static_cast<uint32_t>(viewport.height));
#else
			uint32_t x = 0;
			uint32_t y = 0;
			vk::Offset2D offset(x, y);

			vk::Rect2D scissor{};
			scissor.offset = offset;
			scissor.extent = extent;
#endif

			for(auto&& x : commandBufferData) {
				x.f(commandBuffers, framebuffers, RenderPass, scissor, viewport, x.data);
			}
		}
	} // ns supp
} // ns vk