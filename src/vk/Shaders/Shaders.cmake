# include ("${CMAKE_CURRENT_LIST_DIR}/vkCube/vkCube.cmake")
# include ("${CMAKE_CURRENT_LIST_DIR}/simplest_v/simplest_v.cmake")

add_library(Shaders STATIC "${CMAKE_CURRENT_LIST_DIR}/Shaders.cpp")
target_link_libraries(Shaders PRIVATE Vulkan::Vulkan)