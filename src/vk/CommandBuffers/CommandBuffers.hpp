#ifndef APP_COMMANDBUFFERS
#define APP_COMMANDBUFFERS

#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include "../../trash/dbg.h"

namespace vk {
	namespace supp {
		void set_CommandBuffers(
			std::vector<vk::raii::CommandBuffer>& CommandBuffers,
			const std::vector<vk::raii::Framebuffer>& SwapchainFramebuffers,
			const vk::raii::CommandPool& CommandPool,
			const vk::raii::Device& Device,
			const vk::raii::RenderPass& RenderPass,
			const vk::Extent2D& SwapchainExtent,
			const vk::raii::Pipeline& Pipeline,
			const vk::raii::Buffer& VertexBuffer,
			const vk::raii::Buffer& IndexBuffer,
			const std::vector<unsigned short>& Indices
		);
	}
}

#if 0
struct App_CommandBuffers {
	private:
		std::vector<vk::raii::CommandBuffer> CommandBuffers;
	private:
		std::vector<vk::raii::Framebuffer>	&SwapchainFramebuffers;
		vk::raii::CommandPool								&CommandPool;
		vk::raii::Device										&Device;
		vk::raii::RenderPass								&RenderPass;
		vk::Extent2D												&SwapchainExtent;
		vk::raii::Pipeline									&Pipeline;
		vk::raii::Buffer										&VertexBuffer;
		vk::raii::Buffer										&IndexBuffer;
		const std::vector<unsigned short>		&Indices;
	public:
		void update_CommandBuffers();
		// void destroy_command_buffers();
	public:
		App_CommandBuffers(
							std::vector<vk::raii::Framebuffer> &SwapchainFramebuffers_,
							vk::raii::CommandPool &CommandPool_,
							vk::raii::Device &Device_,
							vk::raii::RenderPass &RenderPass_, 
							vk::Extent2D &SwapchainExtent_,
							vk::raii::Pipeline &Pipeline_,
							vk::raii::Buffer &VertexBuffer_,
							vk::raii::Buffer &IndexBuffer_,
							const std::vector<unsigned short> &Indices_)
							:
							SwapchainFramebuffers(SwapchainFramebuffers_),
							CommandPool(CommandPool_),
							Device(Device_),
							RenderPass(RenderPass_),
							SwapchainExtent(SwapchainExtent_),
							Pipeline(Pipeline_),
							VertexBuffer(VertexBuffer_),
							IndexBuffer(IndexBuffer_),
							Indices(Indices_)
		{
			update_CommandBuffers();
			dbgs << "Command Buffers Created!\n";
		};

		std::vector<vk::raii::CommandBuffer>& get_CommandBuffers() { return CommandBuffers; };
};
#endif

#endif
