#include "svPipeline.hpp"

#if 0
namespace simplest_v {
	vk::raii::Pipeline get_PipeLine_SV(
		const vk::raii::Device& Device,
		const vk::raii::RenderPass& RenderPass,
		const vk::Extent2D& Extent
	) {
		ShaderModuleHolder.push_back(
			{
				std::move(vk::supp::installShader(vert, Device)),
				std::move(vk::supp::installShader(frag, Device))
			}
		);

		auto& modules = ShaderModuleHolder.back();
		dbgs << &modules << " | f:" << &modules.first << " s:" << &modules.second << std::endl;
		vk::PipelineShaderStageCreateInfo vertShaderStageInfo(
			vk::PipelineShaderStageCreateFlags(),
			vk::ShaderStageFlagBits::eVertex,
			modules.first, //StoredVertexID,
			"main",
			nullptr,
			nullptr
		);

		vk::PipelineShaderStageCreateInfo fragShaderStageInfo(
			vk::PipelineShaderStageCreateFlags(),
			vk::ShaderStageFlagBits::eFragment,
			modules.second, // StoredFragmentID,
			"main",
			nullptr,
			nullptr
		);

		std::array<vk::PipelineShaderStageCreateInfo, 2> shaderStages = { vertShaderStageInfo, fragShaderStageInfo };
		std::array<vk::VertexInputBindingDescription, 1> vertBindDesc = { Vertex::getBindingDescription() };
		std::array<vk::VertexInputAttributeDescription, 2> vertAttribDesc = Vertex::getAttributeDescriptions();

#if 0
		unsigned stride = 3 * sizeof(float);
		std::array<vk::VertexInputBindingDescription, 3> vertBindDesc;
		vertBindDesc[0].binding = 0;
		vertBindDesc[0].stride = stride;
		vertBindDesc[0].inputRate = vk::VertexInputRate::eVertex;
		vertBindDesc[1].binding = 1;
		vertBindDesc[1].stride = stride;
		vertBindDesc[1].inputRate = vk::VertexInputRate::eVertex;
		vertBindDesc[2].binding = 2;
		vertBindDesc[2].stride = stride;
		vertBindDesc[2].inputRate = vk::VertexInputRate::eVertex;

		std::array<vk::VertexInputAttributeDescription, 3> vertAttribDesc;
		vertAttribDesc[0].location = 0;
		vertAttribDesc[0].binding = 0;
		vertAttribDesc[0].format = vk::Format::eR32G32B32Sfloat;
		vertAttribDesc[0].offset = 0;
		vertAttribDesc[1].location = 1;
		vertAttribDesc[1].binding = 1;
		vertAttribDesc[1].format = vk::Format::eR32G32B32Sfloat;
		vertAttribDesc[1].offset = 0;
		vertAttribDesc[2].location = 2;
		vertAttribDesc[2].binding = 2;
		vertAttribDesc[2].format = vk::Format::eR32G32B32Sfloat;
		vertAttribDesc[2].offset = 0;
#endif

		vk::PipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = vk::StructureType::ePipelineVertexInputStateCreateInfo;
		vertexInputInfo.flags = vk::PipelineVertexInputStateCreateFlags();
		vertexInputInfo.vertexBindingDescriptionCount = (unsigned)vertBindDesc.size();
		vertexInputInfo.vertexAttributeDescriptionCount = (unsigned)vertAttribDesc.size();
		vertexInputInfo.pVertexBindingDescriptions = vertBindDesc.data();
		vertexInputInfo.pVertexAttributeDescriptions = vertAttribDesc.data();

		vk::PipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = vk::StructureType::ePipelineInputAssemblyStateCreateInfo;
		inputAssembly.flags = vk::PipelineInputAssemblyStateCreateFlags();
		inputAssembly.topology = vk::PrimitiveTopology::eTriangleList;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		vk::Viewport viewport{};
		viewport.x = 0.0f; // 
		viewport.y = 0.0f; // left botom corner in px(float)
		viewport.width = Extent.width; // 
		viewport.height = Extent.height; // resolution 
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		uint32_t x = 0;
		uint32_t y = 0;
		vk::Offset2D offset(x, y);

		vk::Rect2D scissor{};
		scissor.offset = offset;
		scissor.extent = Extent;

		vk::PipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = vk::StructureType::ePipelineViewportStateCreateInfo;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		vk::PipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = vk::StructureType::ePipelineRasterizationStateCreateInfo;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = vk::PolygonMode::eLine; // vk::PolygonMode::eFill; 
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = vk::CullModeFlagBits::eNone;
		rasterizer.frontFace = vk::FrontFace::eClockwise;
		rasterizer.depthBiasEnable = VK_FALSE;
		rasterizer.depthBiasConstantFactor = 0.0f;
		rasterizer.depthBiasClamp = 0.0f;
		rasterizer.depthBiasSlopeFactor = 0.0f;

		vk::SampleMask sampleMask = UINT_MAX; // uint32_t

		vk::PipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = vk::StructureType::ePipelineMultisampleStateCreateInfo;
		multisampling.flags = vk::PipelineMultisampleStateCreateFlags();
		multisampling.rasterizationSamples = vk::SampleCountFlagBits::e16;
		multisampling.sampleShadingEnable = VK_TRUE; // def. false
		multisampling.minSampleShading = 1.0f;
		multisampling.pSampleMask = &sampleMask;
		multisampling.alphaToCoverageEnable = VK_FALSE;
		multisampling.alphaToOneEnable = VK_FALSE;

		vk::StencilOpState stencilOpState{};
		stencilOpState.failOp = vk::StencilOp::eKeep;
		stencilOpState.passOp = vk::StencilOp::eKeep;
		stencilOpState.depthFailOp = vk::StencilOp::eKeep;
		stencilOpState.compareOp = vk::CompareOp::eAlways;
		stencilOpState.compareMask = 0;
		stencilOpState.writeMask = 0;
		stencilOpState.reference = 0;

		VkBool32 depthBuffered = true;

		vk::PipelineDepthStencilStateCreateInfo depthStencilInfo{};
		depthStencilInfo.sType = vk::StructureType::ePipelineDepthStencilStateCreateInfo;
		depthStencilInfo.flags = vk::PipelineDepthStencilStateCreateFlags();
		depthStencilInfo.depthTestEnable = depthBuffered; // bool
		depthStencilInfo.depthWriteEnable = depthBuffered; // bool
		depthStencilInfo.depthCompareOp = vk::CompareOp::eLessOrEqual;
		depthStencilInfo.depthBoundsTestEnable = false;
		depthStencilInfo.stencilTestEnable = false;
		depthStencilInfo.front = stencilOpState;
		depthStencilInfo.back = stencilOpState;
		depthStencilInfo.maxDepthBounds = 0.0f;
		depthStencilInfo.minDepthBounds = 0.0f;

		vk::PipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
		colorBlendAttachment.blendEnable = VK_FALSE;
		colorBlendAttachment.srcColorBlendFactor = vk::BlendFactor::eZero;
		colorBlendAttachment.dstColorBlendFactor = vk::BlendFactor::eZero;
		colorBlendAttachment.colorBlendOp = vk::BlendOp::eAdd;
		colorBlendAttachment.srcAlphaBlendFactor = vk::BlendFactor::eZero;
		colorBlendAttachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
		colorBlendAttachment.alphaBlendOp = vk::BlendOp::eAdd;

		std::array<vk::PipelineColorBlendAttachmentState, 1> colorBlendAttachments = { colorBlendAttachment };

		vk::PipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = vk::StructureType::ePipelineColorBlendStateCreateInfo;
		colorBlending.flags = vk::PipelineColorBlendStateCreateFlags();
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = vk::LogicOp::eCopy;
		colorBlending.attachmentCount = (unsigned)colorBlendAttachments.size();
		colorBlending.pAttachments = colorBlendAttachments.data();
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		std::array<vk::DynamicState, 2> dynamicStates = { vk::DynamicState::eViewport, vk::DynamicState::eScissor };

		vk::PipelineDynamicStateCreateInfo pipelineDynamicState{};
		pipelineDynamicState.sType = vk::StructureType::ePipelineDynamicStateCreateInfo;
		pipelineDynamicState.flags = vk::PipelineDynamicStateCreateFlags();
		pipelineDynamicState.dynamicStateCount = (unsigned)dynamicStates.size();
		pipelineDynamicState.pDynamicStates = dynamicStates.data();

		LayoutHolder.push_back(std::move(get_PipelineLayout(Device)));

		vk::GraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = vk::StructureType::eGraphicsPipelineCreateInfo;
		pipelineInfo.flags = vk::PipelineCreateFlags();
		pipelineInfo.stageCount = (unsigned)shaderStages.size();
		pipelineInfo.pStages = shaderStages.data();
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pTessellationState = nullptr;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthStencilInfo;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &pipelineDynamicState;
		pipelineInfo.layout = LayoutHolder.back();
		pipelineInfo.renderPass = RenderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineInfo.basePipelineIndex = -1;

		CacheHolder.push_back(std::move(get_PipelineCache(Device)));

		return vk::raii::Pipeline(Device, CacheHolder.back(), pipelineInfo, nullptr);
	}
} // ns simplest_v

#endif