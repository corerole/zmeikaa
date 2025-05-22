add_library(Window OBJECT "${CMAKE_CURRENT_LIST_DIR}/Window.cpp")
target_link_libraries(Window PRIVATE Vulkan::Vulkan glfw)