#pragma once
#ifndef UBO_VKCUBE
#define UBO_VKCUBE

#include <GLM/glm.hpp>

namespace vkcube {
	struct UBO {
		glm::mat4 modelview;
		glm::mat4 modelviewprojection;
		glm::vec4 normal[3];
	};
}
#endif