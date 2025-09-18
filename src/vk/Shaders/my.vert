

layout (loaction = 0) in vec3 aPos;
layout (loaction = 0) in vec3 aColour;
layout (loaction = 0) out vec3 vColour;

layout (std140) uniform Matrices {
	mat4 model;
	mat4 view;
	mat4 projection;
}

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vColour = aColour;
}