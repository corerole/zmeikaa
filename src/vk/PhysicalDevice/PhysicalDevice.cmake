add_library(PhysicalDevice OBJECT "${CMAKE_CURRENT_LIST_DIR}/PhysicalDevice.cpp")
target_link_libraries(PhysicalDevice PRIVATE Vulkan::Vulkan dbg)
