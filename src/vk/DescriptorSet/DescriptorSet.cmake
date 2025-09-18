add_library(DescriptorSet OBJECT "${CMAKE_CURRENT_LIST_DIR}/DescriptorSet.cpp")
target_link_libraries(DescriptorSet PRIVATE Vulkan::Vulkan dbg)