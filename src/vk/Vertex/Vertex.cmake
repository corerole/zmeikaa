add_library(Vertex OBJECT "${CMAKE_CURRENT_LIST_DIR}/Vertex.cpp")
target_link_libraries(Vertex PRIVATE Vulkan::Vulkan dbg glm::glm)
