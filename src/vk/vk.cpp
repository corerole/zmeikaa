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


#if 1
#define EXCEPTION 1
#endif

void run_vk(App_Window& wnd)
#ifndef EXCEPTION
{
#else
try {
#endif // !EXCEPTION
	vk::raii::Context context;
	App_Instance				vk_instance(context);
	// App_DebugUtils			vk_debugutils(vk_instance.get());
	App_Surface					vk_surface(wnd.get(),	vk_instance.get());
	App_PhysicalDevice	vk_physicaldevice(vk_instance.get());
	App_QueueFamily			vk_queuefamily(vk_physicaldevice.get(), vk_surface.get());
	App_LogicalDevice		vk_logicaldevice(vk_physicaldevice.get(), vk_queuefamily);
	DebugMarker					marker(vk_logicaldevice.get());
	App_LogicalQueue		vk_logicalqueue(vk_logicaldevice.get(), vk_queuefamily);
	App_Swapchain				vk_swapchain(vk_physicaldevice.get(), vk_surface.get(), wnd, vk_logicaldevice.get(), vk_queuefamily);
	App_ImageViews			vk_imageviews(vk_logicaldevice.get(), vk_swapchain.get(), vk_swapchain.get_SurfaceFormatKHR(), vk_swapchain.get_Extent2D());
	App_RenderPass			vk_renderpass(vk_logicaldevice.get(), vk_imageviews.get_SwapchainImageFormat());
	App_PipeLines				vk_pipelines(vk_logicaldevice.get(),	vk_imageviews.get_SwapchainExtent(), vk_renderpass.get_RenderPass());
	App_Framebuffer			vk_framebuffer(vk_imageviews.get_SwapchainImageViews(), vk_logicaldevice.get(), vk_renderpass.get_RenderPass(), vk_imageviews.get_SwapchainExtent());
	App_CommandPool			vk_commandpool(vk_logicaldevice.get(), vk_queuefamily);
	bool DeviceMemMap2 = false;
	uint32_t MaxFramesInFlight = MAX_FRAMES_IN_FLIGHT;
	App_Buffers					vk_buffers(vk_logicaldevice.get(), vk_physicaldevice.get(), vk_commandpool.get(), vk_logicalqueue.getGraphicsQueue(), DeviceMemMap2, Vertices, Indices);
	App_CommandBuffers	vk_commandbuffers(vk_framebuffer.get_SwapchainFramebuffers(), vk_commandpool.get(), vk_logicaldevice.get(), vk_renderpass.get_RenderPass(), vk_imageviews.get_SwapchainExtent(), vk_pipelines.get(), vk_buffers.get_VertexBuffer(), vk_buffers.get_IndexBuffer(), Indices);
	App_SyncObjects			vk_syncobjects(vk_imageviews.get_SwapchainImages(), vk_logicaldevice.get(), MaxFramesInFlight);
	App_Renderer				vk_renderer(wnd, vk_commandpool, vk_logicaldevice, vk_syncobjects, vk_swapchain,
																	vk_imageviews, vk_renderpass, vk_pipelines, vk_framebuffer, vk_commandbuffers,
																	vk_logicalqueue, vk_buffers, &MaxFramesInFlight);

	dbgs << "Enter in loop... \n";
	while (!glfwWindowShouldClose(wnd.get())) {
		glfwPollEvents();
		vk_renderer.render_frame();
	}

	vk_logicaldevice.get().waitIdle();
#ifndef EXCEPTION
}
#else
} catch (vulkan_error& E) {
	std::cerr << "Vulkan error: " << E.Res << " " << E.what() << std::endl;
	switch (E.Res) {
	case vk::Result::eErrorOutOfHostMemory:
		std::cerr << "VK_ERROR_OUT_OF_HOST_MEMORY\n";
		break;
	case vk::Result::eErrorOutOfDeviceMemory:
		std::cerr << "VK_ERROR_OUT_OF_DEVICE_MEMORY\n";
		break;
	case vk::Result::eErrorDeviceLost:
		std::cerr << "VK_ERROR_DEVICE_LOST\n";
		break;
	default: { std::cerr << "VK error\n"; }
	}
} catch (std::exception& E) {
	std::cerr << "Standard error: " << E.what() << std::endl;
} catch (...) {
	std::cerr << "Unknown error\n";
}
#endif
