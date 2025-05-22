add_library(Shaders OBJECT "${CMAKE_CURRENT_LIST_DIR}/Shaders.cpp")
target_link_libraries(Shaders PRIVATE Vulkan::Vulkan dbg Vertex)
