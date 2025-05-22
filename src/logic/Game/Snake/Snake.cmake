include("${CMAKE_CURRENT_LIST_DIR}/Head/Head.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Tail/Tail.cmake")

add_library(Snake OBJECT "${CMAKE_CURRENT_LIST_DIR}/Snake.cpp")
target_link_libraries(Snake PRIVATE Head Tail)
