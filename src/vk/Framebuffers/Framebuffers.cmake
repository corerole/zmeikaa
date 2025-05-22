add_library(Framebuffers OBJECT "${CMAKE_CURRENT_LIST_DIR}/Framebuffers.cpp")
target_link_libraries(Framebuffers PRIVATE Vulkan::Vulkan dbg)
