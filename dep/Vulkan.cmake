find_package(Vulkan REQUIRED)

add_library(VulkanHppModule)
target_sources(VulkanHppModule PRIVATE
  FILE_SET CXX_MODULES
  BASE_DIRS ${Vulkan_INCLUDE_DIR}
  FILES ${Vulkan_INCLUDE_DIR}/vulkan/vulkan.cppm
)

include_directories(${Vulkan_INCLUDE_DIR})
# link_directories()

target_compile_features( VulkanHppModule PUBLIC cxx_std_20 )
target_link_libraries( VulkanHppModule PUBLIC Vulkan::Vulkan )
