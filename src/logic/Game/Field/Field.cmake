add_library(Field OBJECT "${CMAKE_CURRENT_LIST_DIR}/Field.cpp")
link_libraries(Field PRIVATE dbg Snake)