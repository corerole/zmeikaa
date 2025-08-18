#ifndef APP_RENDERER
#define APP_RENDERER

#include <vulkan/vulkan_raii.hpp>
#include <stdexcept>
#include <array>
#include <vector>
#include <ranges>
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

namespace {
static inline std::vector<vk::raii::ImageView> proxy_init_ImageViews(
	const vk::raii::Device& device,
	const vk::SurfaceFormatKHR& SurfaceFormat,
	const std::vector<vk::Image>& swapchain_images
) {
	std::vector<vk::raii::ImageView> swapchain_imageviews;
	vk::supp::set_ImageViews(
		device,
		SurfaceFormat.format,
		swapchain_images,
		swapchain_imageviews
	);
	return swapchain_imageviews;
}

static inline std::vector<vk::raii::CommandBuffer> proxy_init_CommandBuffers(
	const std::vector<vk::raii::Framebuffer>& swapchain_framebuffers,
	const vk::raii::CommandPool& commandpool,
	const vk::raii::Device& device,
	const vk::raii::RenderPass& renderpass,
	const vk::Extent2D& extent,
	const vk::raii::Pipeline& pipeline,
	const vk::raii::Buffer& VertexBuffer,
	const vk::raii::Buffer& IndexBuffer,
	const std::vector<unsigned short>& Indices
) {
	std::vector<vk::raii::CommandBuffer> command_buffers;
	vk::supp::set_CommandBuffers(
		command_buffers,
		swapchain_framebuffers,
		commandpool,
		device,
		renderpass,
		extent,
		pipeline,
		VertexBuffer,
		IndexBuffer,
		Indices
	);
	return command_buffers;
}
std::vector<vk::raii::Framebuffer> proxy_init_SwapchainFramebuffers(
	const vk::raii::Device& device,
	const vk::raii::RenderPass& renderpass,
	const vk::Extent2D& extent,
	const std::vector<vk::raii::ImageView>& swapchain_imageviews
) {
	std::vector<vk::raii::Framebuffer> swapchain_framebuffers;
	vk::supp::set_SwapchainFramebuffers(
		swapchain_framebuffers,
		device,
		renderpass,
		extent,
		swapchain_imageviews
	);
	return swapchain_framebuffers;
}

} // annon ns

struct App_Renderer {
	private:
		uint32_t CurrentFrame = 0;
	private:
		std::vector<vk::raii::Semaphore> ImageAvailableSemaphores;
		std::vector<vk::raii::Semaphore> RenderFinishedSemaphores;
		std::vector<vk::raii::Fence> InFlightFences;
		std::vector<vk::raii::Fence> ImagesInFlight;
	private:
		const vk::raii::Device& device;
		const vk::raii::PhysicalDevice& physical_device;
		const vk::raii::SurfaceKHR& surface;
		const std::pair<uint32_t, uint32_t>& GaPFQ;
		const vk::SurfaceFormatKHR& surface_format;
		vk::Extent2D& extent;
		const vk::raii::ShaderModule& StoredVertexID;
		const vk::raii::ShaderModule& StoredFragmentID;
		const vk::raii::PipelineCache& pipeline_cache;
		const vk::raii::PipelineLayout& pipeline_layout;
		const vk::raii::CommandPool& commandpool;
		const vk::raii::Buffer& VertexBuffer;
		const vk::raii::Buffer& IndexBuffer;
		const vk::raii::Queue& graphics_queue;
		const vk::raii::Queue& present_queue;
	private:
		GLFWwindow* window;
	private:
		const uint32_t& FramesInFlight;
		bool& FramebufferResized;
	private:
		std::unique_ptr<vk::raii::SwapchainKHR> upSwapchain;
		std::unique_ptr<vk::raii::RenderPass> upRenderpass;
		std::unique_ptr<vk::raii::Pipeline> upPipeline;
	private:
		std::vector<vk::Image> swapchain_images;
		std::vector<vk::raii::ImageView> swapchain_imageviews;
		std::vector<vk::raii::Framebuffer> swapchain_framebuffers;
		std::vector<vk::raii::CommandBuffer> command_buffers;
	private:
		void resize_ImagesInFlight();
		void update_SyncObjects();
		void update_Swapchain();
	public:
		void render_frame();
	public:
		App_Renderer(
			const vk::raii::Device& device,
			const vk::raii::PhysicalDevice& physical_device,
			const vk::raii::SurfaceKHR& surface,
			const std::pair<uint32_t, uint32_t>& GaPFQ,
			const vk::SurfaceFormatKHR& surface_format,
			vk::Extent2D& extent,
			const vk::raii::ShaderModule& StoredVertexID,
			const vk::raii::ShaderModule& StoredFragmentID,
			const vk::raii::PipelineCache& pipeline_cache,
			const vk::raii::PipelineLayout& pipeline_layout,
			const vk::raii::CommandPool& commandpool,
			const vk::raii::Buffer& VertexBuffer,
			const vk::raii::Buffer& IndexBuffer,
			const vk::raii::Queue& graphics_queue,
			const vk::raii::Queue& present_queue,
			GLFWwindow* window,
			const uint32_t& FramesInFlight,
			bool& FramebufferResized
		)	:
		device(device),
		physical_device(physical_device),
		surface(surface),
		GaPFQ(GaPFQ),
		surface_format(surface_format),
		extent(extent),
		StoredVertexID(StoredVertexID),
		StoredFragmentID(StoredFragmentID),
		pipeline_cache(pipeline_cache),
		pipeline_layout(pipeline_layout),
		commandpool(commandpool),
		VertexBuffer(VertexBuffer),
		IndexBuffer(IndexBuffer),
		graphics_queue(graphics_queue),
		present_queue(present_queue),
		window(window),
		FramesInFlight(FramesInFlight),
		FramebufferResized(FramebufferResized),
		upSwapchain(
			std::make_unique<vk::raii::SwapchainKHR>(
				vk::supp::get_Swapchain(
					device,
					physical_device,
					surface,
					GaPFQ,
					surface_format,
					extent
				)
			)
		),
		upRenderpass(
			std::make_unique<vk::raii::RenderPass>(
				vk::supp::get_RenderPass(
					device,
					surface_format.format
				)
			)
		),
		upPipeline(
			std::make_unique<vk::raii::Pipeline>(
				vk::supp::get_PipeLine(
					device,
					StoredVertexID,
					StoredFragmentID,
					extent,
					*upRenderpass,
					pipeline_cache,
					pipeline_layout
				)
			)
		),
		swapchain_images((*upSwapchain).getImages()),
		swapchain_imageviews(
			proxy_init_ImageViews(
				device,
				surface_format,
				swapchain_images
			)
		),
		swapchain_framebuffers(
			proxy_init_SwapchainFramebuffers(
				device,
				*upRenderpass,
				extent,
				swapchain_imageviews
			)
		),
		command_buffers(
			proxy_init_CommandBuffers(
				swapchain_framebuffers,
				commandpool,
				device,
				*upRenderpass,
				extent,
				*upPipeline,
				VertexBuffer,
				IndexBuffer,
				Indices
			)
		)
		{
			update_SyncObjects();
#if 0
			vk::supp::set_CommandBuffers(
				command_buffers,
				swapchain_framebuffers,
				commandpool,
				device,
				renderpass,
				extent,
				pipeline,
				VertexBuffer,
				IndexBuffer,
				Indices
			);
#endif
		}
};

#if 0
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
#endif

#endif // !APP_RENDERER