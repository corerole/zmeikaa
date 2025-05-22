#include "../../trash/dbg.h"
#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include <algorithm>
#include "../Vertex/Vertex.h"

#if 0
const std::vector<Vertex> Vertices = { {{-1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}},	// (0, 0) left upper    
									  {{1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},		// (1, 0) right upper
									  {{1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}},		// (1, 1) right down
									  {{-1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}} };	// (0, 1) left down



const std::vector<unsigned short> Indices = { 0, 1, 2, 2, 3, 0 };
#endif
