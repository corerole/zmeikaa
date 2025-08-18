#ifndef APP_PIPELINES
#define APP_PIPELINES

#include "../../trash/dbg.h"
#include "../Vertex/Vertex.h"
#include "../Shaders/Shaders.hpp"
#include <vulkan/vulkan_raii.hpp>
#include <vector>
#include <memory>

namespace vk {
	namespace supp {
		vk::raii::Pipeline get_PipeLine(
			const vk::raii::Device& Device,
			const vk::raii::ShaderModule& StoredVertexID,
			const vk::raii::ShaderModule& StoredFragmentID,
			const vk::Extent2D& SwapchainExtent,
			const vk::raii::RenderPass& RenderPass,
			const vk::raii::PipelineCache& PipelineCache,
			const vk::raii::PipelineLayout& PipelineLayout
		);

		vk::raii::PipelineLayout get_PipelineLayout(const vk::raii::Device& Device);
		vk::raii::PipelineCache get_PipelineCache(const vk::raii::Device& Device);
	}
}

#if 0
struct App_PipeLines {
	private:
		std::unique_ptr<vk::raii::ShaderModule>		StoredVertexID;
		std::unique_ptr<vk::raii::ShaderModule>		StoredFragmentID;
		std::unique_ptr<vk::raii::PipelineLayout>	PipelineLayout;
		std::unique_ptr<vk::raii::Pipeline>			GraphicsPipeline;
		std::unique_ptr<vk::raii::PipelineCache>	PipelineCache;
	private:
		vk::raii::Device			&Device;
		vk::Extent2D				&SwapchainExtent;
		vk::raii::RenderPass		&RenderPass;
	public:
		void update_Pipeline();
		void update_Shaders(); // todo
	public:
		vk::raii::PipelineLayout&	get_PipelineLayout()	{ return *PipelineLayout;	}
		vk::raii::Pipeline&			get()					{ return *GraphicsPipeline; }
		vk::raii::ShaderModule&		get_StoredFragmentID()	{ return *StoredFragmentID;	}
		vk::raii::ShaderModule&		get_StoredVertexID()	{ return *StoredVertexID;	}
		App_PipeLines(vk::raii::Device& Device_, vk::Extent2D& SwapchainExtent_, vk::raii::RenderPass& RenderPass_);
};
#endif

#endif // !APP_PIPELINES
