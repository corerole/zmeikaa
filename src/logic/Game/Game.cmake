include("${CMAKE_CURRENT_LIST_DIR}/Snake/Snake.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Field/Field.cmake")

add_library(Game OBJECT "${CMAKE_CURRENT_LIST_DIR}/Game.cpp")
target_link_libraries(Game PRIVATE Field Snake)