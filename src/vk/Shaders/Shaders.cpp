#include "Shaders.hpp"

#if 0
namespace {
	static inline std::vector<char> readFile(const char* Path) {
		std::ifstream ShaderFile;
		ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		ShaderFile.open(Path, std::ios::binary);
		std::istreambuf_iterator<char> Start(ShaderFile), Fin;
		return std::vector<char>(Start, Fin);
	}
}
#endif

namespace vk {
	namespace supp {

		vk::raii::ShaderModule ShaderInstaller::installShader(const std::vector<unsigned char>& ShaderCode) {
			vk::ShaderModuleCreateInfo createInfo{};
			createInfo.sType = vk::StructureType::eShaderModuleCreateInfo;
			createInfo.codeSize = ShaderCode.size();
			createInfo.pCode = reinterpret_cast<const unsigned*>(ShaderCode.data());
			return vk::raii::ShaderModule(Device, createInfo);
		}

#if 0
		vk::raii::ShaderModule installShader(const std::vector<unsigned char>& ShaderCode, const vk::raii::Device& Device) {
			vk::ShaderModuleCreateInfo createInfo{};
			createInfo.sType = vk::StructureType::eShaderModuleCreateInfo;
			createInfo.codeSize = ShaderCode.size();
			// createInfo.pCode = reinterpret_cast<const unsigned*>(ShaderCode.data());
			createInfo.pCode = reinterpret_cast<const unsigned*>(ShaderCode.data());
			return vk::raii::ShaderModule(Device, createInfo);
		}
#endif
	} // ns supp
} // ns vk