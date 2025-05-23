add_library(Field OBJECT "${CMAKE_CURRENT_LIST_DIR}/Field.cpp")
target_link_libraries(Field PRIVATE dbg Snake)