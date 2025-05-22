include ("${CMAKE_CURRENT_LIST_DIR}/Instance/Instance.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/DebugUtils/DebugUtils.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/Surface/Surface.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/PhysicalDevice/PhysicalDevice.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/QueueFamilies/QueueFamilies.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/LogicalDevice/LogicalDevice.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/LogicalQueues/LogicalQueue.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/Swapchain/Swapchain.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/ImageViews/ImageViews.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/RenderPass/RenderPass.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/Vertex/Vertex.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/Shaders/Shaders.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/PipeLines/PipeLines.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/Framebuffers/Framebuffers.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/CommandPool/CommandPool.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/Buffers/Buffers.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/CommandBuffers/CommandBuffers.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/SyncObjects/SyncObjects.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/Renderer/Renderer.cmake")


add_library(vk STATIC "${CMAKE_CURRENT_LIST_DIR}/vk.cpp")
target_link_libraries(
	vk 
	PRIVATE
	Vulkan::Vulkan
	dbg
	Buffers
	DebugMarker
	DebugUtils
	CommandBuffers
	CommandPool
	Framebuffers
	ImageViews
	Instance
	LogicalDevice
	LogicalQueue
	PhysicalDevice
	PipeLines
	QueueFamilies
	Renderer
	RenderPass
	Shaders
	Surface
	Swapchain
	SyncObjects
	Vertex
)

