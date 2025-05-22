add_library(DebugMarker OBJECT "${CMAKE_CURRENT_LIST_DIR}/DebugMarker.cpp")
target_link_libraries(DebugMarker PRIVATE Vulkan::Vulkan dbg)