# CMakeList.txt: проект CMake для zmeikaa; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("zmeikaa")

# include_directories(${glfw_INCLUDE_DIR} ${Vulkan_INCLUDE_DIR} ${glm_INCLUDE_DIR})

include("${CMAKE_CURRENT_LIST_DIR}/dep/dep.cmake")

# target_link_libraries(zmeikaa PRIVATE Vulkan::Vulkan)
# target_link_libraries(zmeikaa PRIVATE glfw)
# target_link_libraries(zmeikaa PRIVATE glm::glm)

include("${CMAKE_CURRENT_LIST_DIR}/src/main.cmake")

set_property(TARGET zmeikaa PROPERTY CXX_STANDARD 23)

