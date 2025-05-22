add_library(LogicalDevice OBJECT "${CMAKE_CURRENT_LIST_DIR}/LogicalDevice.cpp")
target_link_libraries(LogicalDevice PRIVATE Vulkan::Vulkan dbg QueueFamilies)
