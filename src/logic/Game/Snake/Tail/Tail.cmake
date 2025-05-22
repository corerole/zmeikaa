add_library(Tail OBJECT "${CMAKE_CURRENT_LIST_DIR}/Tail.cpp")
target_link_libraries(Tail PRIVATE Head)