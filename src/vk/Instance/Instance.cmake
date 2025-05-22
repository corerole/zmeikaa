add_library(Instance OBJECT "${CMAKE_CURRENT_LIST_DIR}/Instance.cpp")
target_link_libraries(Instance PRIVATE Vulkan::Vulkan dbg Window)