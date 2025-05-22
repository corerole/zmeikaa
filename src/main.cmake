include("${CMAKE_CURRENT_LIST_DIR}/trash/trash.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Window/Window.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/vk/vk.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/logic/logic.cmake")

add_executable (zmeikaa "src/main.cpp" "src/main.hpp")
target_link_libraries(zmeikaa PRIVATE Window vk)

