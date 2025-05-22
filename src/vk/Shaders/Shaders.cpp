#include "Shaders.hpp"

std::vector<char> readFile(const char* Path) {
	std::ifstream ShaderFile;
	ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	ShaderFile.open(Path, std::ios::binary);
	std::istreambuf_iterator<char> Start(ShaderFile), Fin;
	return std::vector<char>(Start, Fin);
}

std::unique_ptr<vk::raii::ShaderModule> installShader(std::vector<char> ShaderCode, vk::raii::Device& Device) {
	vk::ShaderModuleCreateInfo createInfo{};
	createInfo.sType = vk::StructureType::eShaderModuleCreateInfo; // VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = ShaderCode.size();
	createInfo.pCode = reinterpret_cast<const unsigned*>(ShaderCode.data());
	return std::make_unique<vk::raii::ShaderModule>(Device, createInfo);
}