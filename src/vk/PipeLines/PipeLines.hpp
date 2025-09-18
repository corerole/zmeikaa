#pragma once
#ifndef APP_PIPELINES
#define APP_PIPELINES

#include <vulkan/vulkan_raii.hpp>
#include <vector>

namespace vk {
	namespace supp {
		struct Data {
			std::vector<vk::raii::ShaderModule> ShaderModuleHolder;
			vk::raii::PipelineLayout LayoutHolder;
			vk::raii::PipelineCache CacheHolder;
			vk::raii::DescriptorSetLayout descriptorSetLayoutsHolder;
		};

		using PipelineGetter = vk::raii::Pipeline (*)(
			const vk::raii::Device& Device,
			const vk::raii::RenderPass& RenderPass,
			const vk::Extent2D& extent,
			const std::vector<vk::raii::ShaderModule>& shaderModuleHolder,
			const vk::raii::PipelineLayout& pipelineLayout,
			const vk::raii::PipelineCache& pipelineCache
		);
		using PipelineLayoutGetter = vk::raii::PipelineLayout (*)(const vk::raii::Device& Device, const vk::raii::DescriptorSetLayout& DescSet);
		using PipelineCacheGetter = vk::raii::PipelineCache (*)(const vk::raii::Device& Device);
		struct PipelineCreater {
			private:
				const vk::raii::Device& Device;
				const vk::raii::RenderPass& RenderPass;
				const vk::Extent2D& Extent;
			public:
				// std::vector<Data> Holder;
			public:
				PipelineCreater(
					const vk::raii::Device& Device,
					const vk::raii::RenderPass& RenderPass,
					const vk::Extent2D& Extent
				) : 
					Device(Device),
					RenderPass(RenderPass),
					Extent(Extent)
				{
				}
			public:
				vk::raii::PipelineLayout create_PipelineLayout(PipelineLayoutGetter pipelineLayoutGetter, const vk::raii::DescriptorSetLayout& DesLayout) {
					return pipelineLayoutGetter(Device, DesLayout);
				}

				vk::raii::PipelineCache create_PipelineCache(PipelineCacheGetter pipelineCacheGetter) {
					return pipelineCacheGetter(Device);
				}

				vk::raii::Pipeline create_Pipeline(
					PipelineGetter pipelineGetter
					,	const std::vector<vk::raii::ShaderModule>& shaderModuleHolder
					, const vk::raii::PipelineLayout& pipelineLayout
					// , std::vector<vk::raii::DescriptorSetLayout> descriptorSetLayoutHolder
					, const vk::raii::PipelineCache& pipelineCache
				) {
					return pipelineGetter(Device, RenderPass, Extent, shaderModuleHolder, pipelineLayout, pipelineCache);
				}
		};
	}
}

#endif // !APP_PIPELINES
