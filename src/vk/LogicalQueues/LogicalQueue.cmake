add_library(LogicalQueue OBJECT "${CMAKE_CURRENT_LIST_DIR}/LogicalQueue.cpp")
target_link_libraries(LogicalQueue PRIVATE Vulkan::Vulkan QueueFamilies)
