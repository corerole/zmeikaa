add_library(CommandBuffers OBJECT "${CMAKE_CURRENT_LIST_DIR}/CommandBuffers.cpp")
target_link_libraries(CommandBuffers PRIVATE Vulkan::Vulkan dbg)