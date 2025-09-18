include(FetchContent)
include(FindVulkan)

#set(ENV{VULKAN_SDK} "C:\\VulkanSDK\\1.4.321.1\\include")

# include("${CMAKE_CURRENT_LIST_DIR}/Vulkan.cmake")

include("${CMAKE_CURRENT_LIST_DIR}/glfw.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/glm.cmake")