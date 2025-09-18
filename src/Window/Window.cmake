add_library(Window STATIC "${CMAKE_CURRENT_LIST_DIR}/Window.cpp")
target_link_libraries(Window PRIVATE glfw)