add_library(toGraphics OBJECT "${CMAKE_CURRENT_LIST_DIR}/toGraphics.cpp")
target_link_libraries(toGraphics PRIVATE dbg random rgb Vertex)