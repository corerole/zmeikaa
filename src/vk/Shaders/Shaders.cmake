add_library(Shaders STATIC "${CMAKE_CURRENT_LIST_DIR}/Shaders.cpp")
target_link_libraries(Shaders PRIVATE Vulkan::Vulkan)