add_library(QueueFamilies OBJECT "${CMAKE_CURRENT_LIST_DIR}/QueueFamilies.cpp")
target_link_libraries(QueueFamilies PRIVATE Vulkan::Vulkan dbg)
