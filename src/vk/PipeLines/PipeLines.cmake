add_library(PipeLines OBJECT "${CMAKE_CURRENT_LIST_DIR}/PipeLines.cpp")
target_link_libraries(PipeLines PRIVATE Vulkan::Vulkan dbg Vertex Shaders)