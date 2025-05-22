add_library(ImageViews OBJECT "${CMAKE_CURRENT_LIST_DIR}/ImageViews.cpp")
target_link_libraries(ImageViews PRIVATE Vulkan::Vulkan dbg)