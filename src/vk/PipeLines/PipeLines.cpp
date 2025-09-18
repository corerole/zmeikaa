#include "PipeLines.hpp"

#include "../Shaders/Shaders.hpp"

#if 0
namespace {
	static inline vk::raii::PipelineCache get_PipelineCache(const vk::raii::Device& Device) {
		vk::PipelineCacheCreateInfo createInfo{};
		createInfo.sType = vk::StructureType::ePipelineCacheCreateInfo;
		createInfo.pInitialData = nullptr;// data.get_data();
		createInfo.initialDataSize = 0;// data.get_size();

		return vk::raii::PipelineCache(Device, createInfo);
	}

	static inline vk::raii::PipelineLayout get_PipelineLayout(const vk::raii::Device& Device) {
		vk::PipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = vk::StructureType::ePipelineLayoutCreateInfo;
		return vk::raii::PipelineLayout(Device, pipelineLayoutInfo);
	}
}
#endif

namespace vk {
	namespace supp {

	} // ns supp
} // ns vk