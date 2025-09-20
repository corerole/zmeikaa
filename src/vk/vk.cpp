#include "vk.hpp"

#include <chrono>

void run_vk(App_Window& wnd) {
	/* Device Exclusuive */
	vk::raii::Context context;
	vk::raii::Instance instance = vk::supp::get_Instance(context);
	vk::raii::DebugUtilsMessengerEXT messenger = vk::supp::get_DebugUtils(instance);
	vk::raii::SurfaceKHR surface = vk::supp::get_Surface(wnd.get(), instance);
	vk::raii::PhysicalDevice physical_device = vk::supp::get_PhysicalDevice(instance);
	auto GaPQF = vk::supp::get_QueueFamilies(physical_device, surface);
	vk::raii::Device device = vk::supp::get_LogicalDevice(physical_device, GaPQF);
	DebugMarker marker(device);
	vk::raii::CommandPool commandpool = vk::supp::get_CommandPool(device, GaPQF);
	vk::raii::Queue graphics_queue(device, GaPQF.first, 0);
	vk::raii::Queue present_queue(device, GaPQF.second, 0);
	vk::SurfaceFormatKHR surface_format = vk::supp::get_SurfaceFormatKHR(physical_device, surface);
	vk::Extent2D extent = vk::supp::get_Extent2D(physical_device, surface, wnd);
	vk::raii::RenderPass renderpass = vk::supp::get_RenderPass(device, surface_format.format);
	auto divAmem = vk::supp::createDepthResources(device, physical_device, extent, commandpool, graphics_queue);
	vk::raii::ImageView depthImageView = vk::supp::createDepthImageView(device, divAmem.first);

	/* Shader Specific */
	vk::supp::BufferCreater bufferCreater(device, physical_device, commandpool, graphics_queue, false);
	vk::supp::PipelineCreater pipelineCreater(device, renderpass, extent);
	vk::supp::DescriptorSetLayoutCreater dSLC(device);
	vk::supp::ShaderInstaller shaderInstaller(device);
	vk::supp::DescritorPoolCreator DescPoolCreater(device);

	std::vector<vk::DescriptorPoolSize> descPoolSize(1);
	descPoolSize[0].descriptorCount = 1;
	descPoolSize[0].type = vk::DescriptorType::eUniformBuffer;
	auto descPool = DescPoolCreater.create_DescriptorPool({}, descPoolSize);

	vkcube::VkCube vkCube(device, shaderInstaller, renderpass, extent, bufferCreater, descPool, DescPoolCreater);

#if 0
	auto vkCube = vk::supp::collect_ShaderData(pipelineCreater, dSLC, bufferCreater, shaderInstaller, DescPoolCreater);

	auto vVsize = vectorsizeof(vkcube::vVertices);
	auto vCsize = vectorsizeof(vkcube::vColors);
	auto vNsize = vectorsizeof(vkcube::vNormals);
	auto vertex_offset = sizeof(vkcube::UBO);
	auto colors_offset = vertex_offset + vVsize;
	auto normals_offset = colors_offset + vCsize;

	vkcube::vkCube_CommandBufferData vkcube_cbd{
		vkCube.cb_data[0].pipeline,
		vkCube.cb_data[0].pipelineLayout,
		{ vertex_offset, colors_offset, normals_offset },
		{ vkCube.cb_data[0].buffers[0].first, vkCube.cb_data[0].buffers[0].second },
		vkCube.cb_data[0].descSet,
		std::chrono::high_resolution_clock::now()
	};

	vk::supp::CommandBufferData cbdata{};
	cbdata.data = &vkcube_cbd;
	cbdata.f = vkcube::vkCube_set_CommandBuffer;
#endif

	std::vector<vk::supp::CommandBufferData> vcbd;
	vcbd.push_back(vkCube.get_CommandBufferData());

#if 1
	/* send to renderer update function's */
	uint32_t MaxFramesInFlight = MAX_FRAMES_IN_FLIGHT;

	App_Renderer renderer(
		device,
		physical_device,
		surface,
		GaPQF,
		surface_format,
		extent,
		renderpass,
		depthImageView,
		vcbd,
		commandpool,
		graphics_queue,
		present_queue,
		wnd.get(),
		MaxFramesInFlight,
		wnd.get_frabuffer_resized()
	);

	size_t i = 0;
	std::chrono::high_resolution_clock::time_point Start, Fin;
	Start = std::chrono::high_resolution_clock::now();
	while (!glfwWindowShouldClose(wnd.get())) {
		glfwPollEvents();
		renderer.render_frame();
		auto Now = std::chrono::high_resolution_clock::now();
		auto Res = Now - Start;
		auto sec = std::chrono::duration_cast<std::chrono::seconds>(Res).count();
		if(sec) {
			dbgs << "FPS: " << i << std::endl;
			Start = Now;
			i = 0;
		}
		++i;
	}

	device.waitIdle();
#endif
}
