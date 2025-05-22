add_library(Surface OBJECT "${CMAKE_CURRENT_LIST_DIR}/Surface.cpp")
target_link_libraries(Surface PRIVATE Vulkan::Vulkan Window dbg)
