#pragma once
#ifndef APP_SHADERS
#define APP_SHADERS

#include <fstream>
#include <algorithm>
#include <vector>
#include <array>
#include <vulkan/vulkan_raii.hpp>
#include "../../trash/dbg.h"
#include "../Vertex/Vertex.h"
#include "../PipeLines/PipeLines.hpp"
#include "../DescriptorSet/DescriptorSet.hpp"
#include "../Buffers/Buffers.hpp"
#include "simplest_v/simplest_v.hpp"
// #include "vkCube/vkCube.hpp"

namespace vk {
	namespace supp {
		struct ShaderInstaller {
			private:
				const vk::raii::Device& Device;
			public:
				ShaderInstaller(const vk::raii::Device& Device) : Device(Device) {};
				vk::raii::ShaderModule installShader(const std::vector<unsigned char>& ShaderCode);
		};
#if 0
		struct SD {
			std::vector<vk::raii::ShaderModule> shaderModules;
			vk::raii::Pipeline pipeline;
			vk::raii::DescriptorSetLayout descSetLayout;
			vk::raii::PipelineLayout pipelineLayout;
			vk::raii::PipelineCache pipelineCache;
			std::vector<std::pair<vk::raii::Buffer, vk::raii::DeviceMemory>> buffers;
			vk::raii::DescriptorPool descPool;
			vk::raii::DescriptorSet descSet;
		};

		struct ShaderData {
			std::vector<SD> cb_data;
		};

		vk::supp::ShaderData collect_ShaderData(
			vk::supp::PipelineCreater& pipelineCreater,
			vk::supp::DescriptorSetLayoutCreater& descSetLayoutCreater,
			vk::supp::BufferCreater& bufferCreater,
			vk::supp::ShaderInstaller& shaderInstaller,
			vk::supp::DescritorPoolCreator& descPoolCreater
		);
#endif
	} // ns supp
} // ns vk

#endif // !APP_SHADERS
