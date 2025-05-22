add_library(Renderer OBJECT "${CMAKE_CURRENT_LIST_DIR}/Renderer.cpp")
target_link_libraries(Renderer PRIVATE Vulkan::Vulkan
														Window
														dbg
														LogicalDevice
														Swapchain
														ImageViews
														RenderPass
														PipeLines
														Framebuffers
														CommandBuffers
														Buffers
														SyncObjects
														CommandPool
														LogicalQueue)
