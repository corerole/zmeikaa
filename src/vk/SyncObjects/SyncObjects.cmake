add_library(SyncObjects OBJECT "${CMAKE_CURRENT_LIST_DIR}/SyncObjects.cpp")
target_link_libraries(SyncObjects PRIVATE Vulkan::Vulkan dbg)
