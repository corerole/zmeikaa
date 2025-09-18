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
		vk::supp::ShaderData collect_ShaderData(
			vk::supp::PipelineCreater& pipelineCreater,
			vk::supp::DescriptorSetLayoutCreater& descSetLayoutCreater,
			vk::supp::BufferCreater& bufferCreater,
			vk::supp::ShaderInstaller& shaderInstaller,
			vk::supp::DescritorPoolCreator& descPoolCreater
		) {
			vk::supp::ShaderData shaderData;
			{
				std::vector<vk::raii::ShaderModule> shaderModules;
				shaderModules.push_back(shaderInstaller.installShader(vkcube::vert));
				shaderModules.push_back(shaderInstaller.installShader(vkcube::frag));
				auto descSetLayout = descSetLayoutCreater.create_DescriptorSetLayout(vkcube::get_DescriptorSetLayout_vkCube);
				auto pipelineLayout = pipelineCreater.create_PipelineLayout(vkcube::get_PipelineLayout_vkCube, descSetLayout);
				auto pipelineCache = pipelineCreater.create_PipelineCache(vkcube::get_PipelineCache_vkCube);
				auto pipeline = pipelineCreater.create_Pipeline(vkcube::get_Pipeline_vkCube, shaderModules, pipelineLayout, pipelineCache);

				std::vector<vk::DescriptorPoolSize> descPoolSize(1);
				descPoolSize[0].descriptorCount = 1;
				descPoolSize[0].type = vk::DescriptorType::eUniformBuffer;
				auto descPool = descPoolCreater.create_DescriptorPool({}, descPoolSize);

				std::array<vk::DescriptorSetLayout, 1> ls = { *descSetLayout };

				auto descSets = descPoolCreater.allocate_DescriptorSets(descPool, ls);
				
				std::vector<std::pair<vk::raii::Buffer, vk::raii::DeviceMemory>> buffers;

				buffers.push_back(vkcube::get_Buffers_vkCube(bufferCreater));

				vk::DescriptorBufferInfo bufferInfo(buffers[0].first, 0, sizeof(vkcube::UBO));

				std::array<vk::WriteDescriptorSet, 1> wds;
				wds[0].dstSet = descSets[0];
				wds[0].dstBinding = 0;
				wds[0].dstArrayElement = 0;
				wds[0].descriptorCount = 1;
				wds[0].descriptorType = vk::DescriptorType::eUniformBuffer;
				wds[0].pBufferInfo = &bufferInfo;

				descPoolCreater.update_DescriptorSet(wds, {});

				SD sd{
					std::move(shaderModules),
					std::move(pipeline),
					std::move(descSetLayout),
					std::move(pipelineLayout),
					std::move(pipelineCache),
					std::move(buffers),
					std::move(descPool),
					std::move(descSets[0])
				};
				shaderData.cb_data.push_back(std::move(sd));
			}
			return shaderData;
		}

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