add_library(Buffers OBJECT "${CMAKE_CURRENT_LIST_DIR}/Buffers.cpp")
target_link_libraries(Buffers PRIVATE Vulkan::Vulkan dbg Vertex)
