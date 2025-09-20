add_library(vkCube STATIC
	"${CMAKE_CURRENT_LIST_DIR}/vkCube.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/UBO.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/vkCubeShaderData.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/vkCubeShaderSource.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/vkCubeUpdateFunctions.cpp"
)
target_link_libraries(vkCube PRIVATE Vulkan::Vulkan CommandBuffers DescriptorSet Buffers Shaders)