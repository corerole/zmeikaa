include ("${CMAKE_CURRENT_LIST_DIR}/random/random.cmake")

add_library(dbg OBJECT "${CMAKE_CURRENT_LIST_DIR}/dbg.cpp")
add_library(rgb OBJECT "${CMAKE_CURRENT_LIST_DIR}/rgb.cpp")

target_link_libraries(dbg PRIVATE Vulkan::Vulkan)
