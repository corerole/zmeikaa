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
	const std::vector<vk::supp::CommandBufferData>& commandBufferData
) {
	std::vector<vk::raii::CommandBuffer> command_buffers;
	vk::supp::set_CommandBuffers(
		command_buffers,
		swapchain_framebuffers,
		commandpool,
		device,
		renderpass,
		extent,
		commandBufferData
	);
	return command_buffers;
}
std::vector<vk::raii::Framebuffer> proxy_init_SwapchainFramebuffers(
	const vk::raii::Device& device,
	const vk::raii::RenderPass& renderpass,
	const vk::Extent2D& extent,
	const std::vector<vk::raii::ImageView>& swapchain_imageviews,
	const vk::raii::ImageView& depthImageView
) {
	std::vector<vk::raii::Framebuffer> swapchain_framebuffers;
	vk::supp::set_SwapchainFramebuffers(
		swapchain_framebuffers,
		device,
		renderpass,
		extent,
		swapchain_imageviews,
		depthImageView
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
		const vk::raii::CommandPool& commandpool;
		const vk::raii::Queue& graphics_queue;
		const vk::raii::Queue& present_queue;
	private:
		GLFWwindow* window;
	private:
		const uint32_t& FramesInFlight;
		bool& FramebufferResized;
	private:
		std::unique_ptr<vk::raii::SwapchainKHR> upSwapchain;
		const vk::raii::RenderPass& renderpass;
		const vk::raii::ImageView& depthImageView;
	private:
		const std::vector<vk::supp::CommandBufferData>& commandBufferData;
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
			const vk::raii::RenderPass& renderpass,
			const vk::raii::ImageView& depthImageView,
			const std::vector<vk::supp::CommandBufferData>& commandBufferData,
			const vk::raii::CommandPool& commandpool,
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
		renderpass(renderpass),
		depthImageView(depthImageView),
		commandBufferData(commandBufferData),
		commandpool(commandpool),
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
				renderpass,
				extent,
				swapchain_imageviews,
				depthImageView
			)
		),
		command_buffers(
			proxy_init_CommandBuffers(
				swapchain_framebuffers,
				commandpool,
				device,
				renderpass,
				extent,
				commandBufferData
			)
		)
		{
			update_SyncObjects();
		}
};

#endif // !APP_RENDERER