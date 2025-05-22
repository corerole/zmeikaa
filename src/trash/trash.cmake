include ("${CMAKE_CURRENT_LIST_DIR}/random/random.cmake")

add_library(dbg STATIC "${CMAKE_CURRENT_LIST_DIR}/dbg.cpp")
add_library(rgb STATIC "${CMAKE_CURRENT_LIST_DIR}/rgb.cpp")

target_link_libraries(dbg PRIVATE Vulkan::Vulkan)
