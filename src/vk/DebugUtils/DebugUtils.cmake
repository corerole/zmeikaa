include("${CMAKE_CURRENT_LIST_DIR}/DebugMarker/DebugMarker.cmake")

add_library(DebugUtils OBJECT "${CMAKE_CURRENT_LIST_DIR}/DebugUtils.cpp")
target_link_libraries(DebugUtils PRIVATE Vulkan::Vulkan dbg)