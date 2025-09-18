add_library(simplest_v OBJECT
	"${CMAKE_CURRENT_LIST_DIR}/simplest_v.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/shader_bin.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/svPipeline.cpp"
)
target_link_libraries(simplest_v PRIVATE Vulkan::Vulkan dbg Vertex)
