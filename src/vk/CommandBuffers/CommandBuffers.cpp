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
			const vk::Extent2D& SwapchainExtent,
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

			commandBuffers = Device.allocateCommandBuffers(allocInfo);
			auto viewport = get_Viewport(SwapchainExtent, 16, 9);

			uint32_t x = 0;
			uint32_t y = 0;
			vk::Offset2D offset(x, y);

			vk::Rect2D scissor{};
			scissor.offset = offset;
			scissor.extent = SwapchainExtent;
#if 0
			// vk::Viewport viewports[] = { viewport };
			// vk::Rect2D scissors[]  = { scissor };
#endif

			for(auto&& x : commandBufferData) {
				x.f(commandBuffers, framebuffers, RenderPass, scissor, viewport, x.data);
			}

#if 0
			for (unsigned i = 0; i < CommandBuffers.size(); ++i) {
				vk::CommandBufferBeginInfo beginInfo{};
				beginInfo.sType = vk::StructureType::eCommandBufferBeginInfo;
				beginInfo.flags = vk::CommandBufferUsageFlagBits::eSimultaneousUse;
				CommandBuffers[i].begin(beginInfo);
				vk::ClearValue clearColor;
				
				vk::RenderPassBeginInfo renderPassInfo(
					RenderPass,
					SwapchainFramebuffers[i],
					scissor,
					clearColor
				);

				CommandBuffers[i].beginRenderPass(renderPassInfo, vk::SubpassContents::eInline);
				for(unsigned j = 0; j < shaderData.cb_data.size(); ++j) {
					shaderData.cb_update_f[i](CommandBuffers[i], RenderPass, SwapchainFramebuffers[i], shaderData.cb_data[j]);
				}
				CommandBuffers[i].endRenderPass();
				CommandBuffers[i].end();
			}
#endif
		}
	} // ns supp
} // ns vk