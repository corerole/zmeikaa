#include "vk.hpp"

#include "Instance/Instance.hpp"
#include "DebugUtils/DebugUtils.hpp"
#include "DebugUtils/DebugMarker/DebugMarker.hpp"
#include "Surface/Surface.hpp"
#include "PhysicalDevice/PhysicalDevice.hpp"
#include "QueueFamilies/QueueFamilies.hpp"
#include "LogicalDevice/LogicalDevice.hpp"
#include "LogicalQueues/LogicalQueue.hpp"
#include "Swapchain/Swapchain.hpp"
#include "ImageViews/ImageViews.hpp"
#include "RenderPass/RenderPass.hpp"
#include "Shaders/Shaders.hpp"
#include "PipeLines/PipeLines.hpp"
#include "Framebuffers/Framebuffers.hpp"
#include "CommandPool/CommandPool.hpp"
#include "Buffers/Buffers.hpp"
#include "CommandBuffers/CommandBuffers.hpp"
#include "SyncObjects/SyncObjects.hpp"
#include "Renderer/Renderer.hpp"

void run_vk(App_Window& wnd) {
	vk::raii::Context context;
	vk::raii::Instance instance = vk::supp::get_Instance(context);
	vk::raii::DebugUtilsMessengerEXT messenger = vk::supp::get_DebugUtils(instance);
	vk::raii::SurfaceKHR surface = vk::supp::get_Surface(wnd.get(), instance);
	vk::raii::PhysicalDevice physical_device = vk::supp::get_PhysicalDevice(instance);
	auto GaPQF = vk::supp::get_QueueFamilies(physical_device, surface);
	vk::raii::Device device = vk::supp::get_LogicalDevice(physical_device, GaPQF);
	vk::raii::CommandPool commandpool = vk::supp::get_CommandPool(device, GaPQF);
	DebugMarker marker(device);
	vk::raii::Queue graphics_queue(device, GaPQF.first, 0);
	vk::raii::Queue present_queue(device, GaPQF.second, 0);
	auto StoredVertexID = installShader((readFile(VERTNAME)), device);
	auto StoredFragmentID = installShader((readFile(FRAGNAME)), device);
	vk::SurfaceFormatKHR surface_format = vk::supp::get_SurfaceFormatKHR(physical_device, surface);
	vk::Extent2D extent = vk::supp::get_Extent2D(physical_device, surface, wnd);
	vk::raii::PipelineCache pipeline_cache = vk::supp::get_PipelineCache(device);
	vk::raii::PipelineLayout pipeline_layout = vk::supp::get_PipelineLayout(device);
	bool DeviceMemMap2 = false;
	App_Buffers vk_buffers(device, physical_device, commandpool, graphics_queue, DeviceMemMap2, Vertices, Indices);

	uint32_t MaxFramesInFlight = MAX_FRAMES_IN_FLIGHT;

	App_Renderer renderer(
		device,
		physical_device,
		surface,
		GaPQF,
		surface_format,
		extent,
		StoredVertexID,
		StoredFragmentID,
		pipeline_cache,
		pipeline_layout,
		commandpool,
		vk_buffers.get_VertexBuffer(),
		vk_buffers.get_IndexBuffer(),
		graphics_queue,
		present_queue,
		wnd.get(),
		MaxFramesInFlight,
		wnd.get_frabuffer_resized()
	);

	while (!glfwWindowShouldClose(wnd.get())) {
		glfwPollEvents();
		renderer.render_frame();
	}

	device.waitIdle();


#if 0
	vk::raii::SwapchainKHR swapchain = vk::supp::get_Swapchain(device, physical_device, surface, GaPQF, surface_format, extent);
	std::vector<vk::Image> swapchain_images = swapchain.getImages();
	std::vector<vk::raii::ImageView> swapchain_imageviews;
	vk::supp::set_ImageViews(device, surface_format.format, swapchain_images, swapchain_imageviews);
	vk::raii::RenderPass renderpass = vk::supp::get_RenderPass(device, surface_format.format);
	vk::raii::Pipeline pipeline = vk::supp::get_PipeLine(
		device, StoredVertexID, StoredFragmentID,	extent,
		renderpass,	pipeline_cache,	pipeline_layout
	);
	std::vector<vk::raii::Framebuffer> swapchain_framebuffers;
	vk::supp::set_SwapchainFramebuffers(
		swapchain_framebuffers,
		device,
		renderpass,
		extent,
		swapchain_imageviews
	);

	std::vector<vk::raii::CommandBuffer> command_buffers;

	vk::supp::set_CommandBuffers(
		command_buffers,
		swapchain_framebuffers,
		commandpool,
		device,
		renderpass,
		extent,
		pipeline,
		vk_buffers.get_VertexBuffer(),
		vk_buffers.get_IndexBuffer(),
		Indices
	);

	uint32_t MaxFramesInFlight = MAX_FRAMES_IN_FLIGHT;

#if 0
	App_SyncObjects vk_syncobjects(
		swapchain_images,
		device,
		MaxFramesInFlight
	);
#endif
#endif

#if 0

	App_Renderer vk_renderer(
		wnd,
		vk_commandpool,
		vk_logicaldevice,
		vk_syncobjects,
		vk_swapchain,
		vk_imageviews,
		vk_renderpass,
		vk_pipelines,
		vk_framebuffer,
		vk_commandbuffers,
		vk_logicalqueue,
		vk_buffers,
		&MaxFramesInFlight
	);

	dbgs << "Enter in loop... \n";
	while (!glfwWindowShouldClose(wnd.get())) {
		glfwPollEvents();
		vk_renderer.render_frame();
	}

	vk_logicaldevice.get().waitIdle();
	#endif
}
