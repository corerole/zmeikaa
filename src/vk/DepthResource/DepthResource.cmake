add_library(DepthResource OBJECT "${CMAKE_CURRENT_LIST_DIR}/DepthResource.cpp")
target_link_libraries(DepthResource PRIVATE Vulkan::Vulkan)
