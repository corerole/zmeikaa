#ifndef APP_RENDERER
#define APP_RENDERER

#include <vulkan/vulkan_raii.hpp>
#include <stdexcept>
#include <vector>
#include "../../Window/Window.hpp"

#include "../LogicalDevice/LogicalDevice.hpp"
#include "../Swapchain/Swapchain.hpp"
#include "../ImageViews/ImageViews.hpp"
#include "../RenderPass/RenderPass.hpp"
#include "../PipeLines/PipeLines.hpp"
#include "../Framebuffers/Framebuffers.hpp"
#include "../CommandBuffers/CommandBuffers.hpp"
#include "../Buffers/Buffers.hpp"
#include "../SyncObjects/SyncObjects.hpp"
#include "../CommandPool/CommandPool.hpp"
#include "../LogicalQueues/LogicalQueue.hpp"


struct App_Renderer {
	private:
		size_t							CurrentFrame = 0;
		bool								*FramebufferResized;
		uint32_t						*FramesInFlight;
	private:
		void								create_swap_chain();
		void								update_swap_chain();
	private:
		App_Window					&Window;
		App_CommandPool			&vk_CommandPool;
		App_LogicalDevice		&vk_LogicalDevice;
		App_SyncObjects			&vk_SyncObjects;
		App_Swapchain				&vk_Swapchain;
		App_ImageViews			&vk_ImageViews;
		App_RenderPass			&vk_RenderPass;
		App_PipeLines				&vk_PipeLines;
		App_Framebuffer			&vk_Framebuffer;
		App_CommandBuffers	&vk_CommandBuffers;
		App_LogicalQueue		&vk_LogicalQueues;
		App_Buffers					&vk_Buffers;
	public:
		void render_frame();
	public:
		App_Renderer(
			App_Window							&Window_,
			App_CommandPool					&vk_CommandPool_,
			App_LogicalDevice				&vk_LogicalDevice_,
			App_SyncObjects					&vk_SyncObjects_,
			App_Swapchain						&vk_Swapchain_,
			App_ImageViews					&vk_ImageViews_,
			App_RenderPass					&vk_RenderPass_,
			App_PipeLines						&vk_PipeLines_,
			App_Framebuffer					&vk_Framebuffer_,
			App_CommandBuffers			&vk_CommandBuffers_,
			App_LogicalQueue				&vk_LogicalQueues_,
			App_Buffers							&vk_Buffers_,
			uint32_t								*FramesInFlight_)
			
			:

			Window(Window_),
			vk_CommandPool(vk_CommandPool_),
			vk_LogicalDevice(vk_LogicalDevice_),
			vk_SyncObjects(vk_SyncObjects_),
			vk_Swapchain(vk_Swapchain_),
			vk_ImageViews(vk_ImageViews_),
			vk_RenderPass(vk_RenderPass_),
			vk_PipeLines(vk_PipeLines_),
			vk_Framebuffer(vk_Framebuffer_),
			vk_CommandBuffers(vk_CommandBuffers_),
			vk_LogicalQueues(vk_LogicalQueues_),
			vk_Buffers(vk_Buffers_)
		{
				FramebufferResized = Window.get_frabuffer_resized();
				FramesInFlight = FramesInFlight_;
		}
};

#endif // !APP_RENDERER