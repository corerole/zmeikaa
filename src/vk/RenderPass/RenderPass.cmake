add_library(RenderPass OBJECT "${CMAKE_CURRENT_LIST_DIR}/RenderPass.cpp")
target_link_libraries(RenderPass PRIVATE Vulkan::Vulkan dbg)