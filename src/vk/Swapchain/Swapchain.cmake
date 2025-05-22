add_library(Swapchain OBJECT "${CMAKE_CURRENT_LIST_DIR}/Swapchain.cpp")
target_link_libraries(Swapchain PRIVATE Vulkan::Vulkan dbg Window QueueFamilies)