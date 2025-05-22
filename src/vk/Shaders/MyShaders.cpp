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



#if 0
typedef unsigned char usc;
struct kvadrat {
	private:
		struct pos {
			size_t x;
			size_t y;
		} pos;
		std::vector<Vertex> Vertices;
		std::vector<unsigned short> Indices;
		struct colour { 
			unsigned char red;
			unsigned char green;
			unsigned char blue;
		} colour;
	public:
		kvadrat(usc r, usc g, usc b, float size, size_t x, size_t y);
};

kvadrat::kvadrat(usc r, usc g, usc b, size_t size, size_t x, size_t y) {
	const float k = (2.0f / size);
	Vertices.resize(4);
	float fr, fg, fb;
	Vertices[0] = { { 1- (1 * x) }, {fr, fg, fb}};

}

size_t plate_size(size_t x, y) {
	a.resize(x * y);
}

void get_vertices(std::vector<Vertex>& vertices, size_t x, size_t y) {
	std::pair<size_t, size_t> resolution = std::make_pair(res_h, res_w);
	
	size_t x = 0, y = 0;
	long double dx = reinterpret_cast<long double>(x);
	long double dy = reinterpret_cast<long double>(y);
	long double AspectRatio = 0;
}
#endif