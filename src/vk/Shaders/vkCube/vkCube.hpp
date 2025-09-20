#ifndef VK_CUBE
#define VK_CUBE

#include "vkCubeShaderSource.hpp"
#include "vkCubeShaderData.hpp"
// #include "vkCubePipeline.hpp"
#include "vkCubeUpdateFunctions.hpp"
// #include "vkCubeBuffer.hpp"

namespace vkcube {
	struct VkCube {
		private:
			vk::raii::DescriptorSetLayout get_DescriptorSetLayout_vkCube(const vk::raii::Device& Device);
			vk::raii::PipelineCache get_PipelineCache_vkCube(const vk::raii::Device& Device);
			vk::raii::PipelineLayout get_PipelineLayout_vkCube(const vk::raii::Device& Device, const vk::raii::DescriptorSetLayout& descLayout);
			vk::raii::Pipeline get_Pipeline_vkCube(
				const vk::raii::Device& Device,
				const vk::raii::RenderPass& RenderPass,
				const vk::Extent2D& Extent,
				const vk::raii::ShaderModule& VertexShaderModule,
				const vk::raii::ShaderModule& FragmentShaderModule,
				const vk::raii::PipelineLayout& pipelineLayout,
				const vk::raii::PipelineCache& pipelineCache
			);
			std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_Buffers_vkCube(vk::supp::BufferCreater& bcá, std::array<size_t, 3>& offsets);
			vk::raii::DescriptorSet get_DescriptorSet_vkCube(
				vk::supp::DescritorPoolCreator& descPoolCreator,
				const vk::raii::DescriptorPool& descPool,
				const vk::raii::DescriptorSetLayout& descSetLayout
			);
			void update_DescriptorSet_vkCube(
				const vk::raii::Buffer& buffer,
				const vk::raii::DescriptorSet& descSet,
				vk::supp::DescritorPoolCreator& descPoolCreator
			);
			std::array<size_t, 3> get_offsets_vkCube();
		private:
			vk::raii::DescriptorSetLayout DescSetLayout;
			vk::raii::PipelineCache PipelineCache;
			vk::raii::PipelineLayout PipelineLayout;
			vk::raii::ShaderModule VertexModule;
			vk::raii::ShaderModule FragmentModule;
			vk::raii::Pipeline Pipeline;
			std::array<size_t, 3> offsets;
			std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> BufferAndMem;
			vk::raii::DescriptorSet DescSet;
		private:
			bool is_inited = false;
			vkcube::vkCube_CommandBufferData cbdata;
		public:
			VkCube(
					const vk::raii::Device& Device
				, vk::supp::ShaderInstaller& shaderInstaller
				, const vk::raii::RenderPass& RenderPass
				, const vk::Extent2D& extent
				, vk::supp::BufferCreater& bufferCreater
				, const vk::raii::DescriptorPool& descPool
				, vk::supp::DescritorPoolCreator& descPoolCreator
			)
			: DescSetLayout(get_DescriptorSetLayout_vkCube(Device))
			, PipelineCache(get_PipelineCache_vkCube(Device))
			, PipelineLayout(get_PipelineLayout_vkCube(Device, DescSetLayout))
			, VertexModule(shaderInstaller.installShader(vkcube::vert))
			, FragmentModule(shaderInstaller.installShader(vkcube::frag))
			,	Pipeline(get_Pipeline_vkCube(Device, RenderPass, extent, VertexModule, FragmentModule, PipelineLayout, PipelineCache))
			, offsets(get_offsets_vkCube())
			, BufferAndMem(get_Buffers_vkCube(bufferCreater, offsets))
			, DescSet(get_DescriptorSet_vkCube(descPoolCreator, descPool, DescSetLayout))
			, cbdata(Pipeline, PipelineLayout, offsets, BufferAndMem, DescSet, std::chrono::high_resolution_clock::now())
			{
				update_DescriptorSet_vkCube(BufferAndMem.first, DescSet, descPoolCreator);
				is_inited = true;
			}
			
			vk::supp::CommandBufferData get_CommandBufferData();
	};
	
}

#endif