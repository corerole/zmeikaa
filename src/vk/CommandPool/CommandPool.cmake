add_library(CommandPool OBJECT "${CMAKE_CURRENT_LIST_DIR}/CommandPool.cpp")
target_link_libraries(CommandPool PRIVATE Vulkan::Vulkan dbg QueueFamilies)
