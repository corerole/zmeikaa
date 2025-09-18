#include "vkCubePipeline.hpp"


namespace vkcube {

	vk::raii::DescriptorSetLayout get_DescriptorSetLayout_vkCube(const vk::raii::Device& Device) {
		std::array<vk::DescriptorSetLayoutBinding, 1> layouts;
		layouts[0].binding;
		layouts[0].descriptorCount = 1;
		layouts[0].descriptorType = vk::DescriptorType::eUniformBuffer;
		layouts[0].pImmutableSamplers;
		layouts[0].stageFlags = vk::ShaderStageFlagBits::eVertex;

		vk::DescriptorSetLayoutCreateInfo descSetLayoutCreateInfo({}, layouts);

		return vk::raii::DescriptorSetLayout(Device, descSetLayoutCreateInfo);
	}

	vk::raii::PipelineLayout get_PipelineLayout_vkCube(const vk::raii::Device& Device, const vk::raii::DescriptorSetLayout& descLayout) {

		vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
		pipelineLayoutCreateInfo.flags = {};
		pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
		pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;
		pipelineLayoutCreateInfo.setLayoutCount = 1;
		pipelineLayoutCreateInfo.pSetLayouts = &(*descLayout);

		return vk::raii::PipelineLayout(Device, pipelineLayoutCreateInfo);;
	}

	vk::raii::PipelineCache get_PipelineCache_vkCube(const vk::raii::Device& Device) {
		vk::PipelineCacheCreateInfo createInfo{};
		createInfo.flags;
		createInfo.initialDataSize;
		createInfo.pInitialData;
		createInfo.pNext;
		return vk::raii::PipelineCache(Device, createInfo);
	}

	vk::raii::Pipeline get_Pipeline_vkCube(
		const vk::raii::Device& Device,
		const vk::raii::RenderPass& RenderPass,
		const vk::Extent2D& Extent,
		const std::vector<vk::raii::ShaderModule>& ShaderModuleHolder,
		const vk::raii::PipelineLayout& pipelineLayout,
		const vk::raii::PipelineCache& pipelineCache
	) {
		vk::PipelineShaderStageCreateInfo vertShaderStageInfo(
			vk::PipelineShaderStageCreateFlags(),
			vk::ShaderStageFlagBits::eVertex,
			ShaderModuleHolder[0],
			"main",
			nullptr,
			nullptr
		);

		vk::PipelineShaderStageCreateInfo fragShaderStageInfo(
			vk::PipelineShaderStageCreateFlags(),
			vk::ShaderStageFlagBits::eFragment,
			ShaderModuleHolder[1],
			"main",
			nullptr,
			nullptr
		);

		std::array<vk::PipelineShaderStageCreateInfo, 2> shaderStages = { vertShaderStageInfo, fragShaderStageInfo };

		std::array<vk::VertexInputBindingDescription, 3> bindingDescription;
		bindingDescription[0].binding = 0;
		bindingDescription[0].stride = 3 * sizeof(float);
		bindingDescription[0].inputRate = vk::VertexInputRate::eVertex;
		bindingDescription[1].binding = 1;
		bindingDescription[1].stride = 3 * sizeof(float);
		bindingDescription[1].inputRate = vk::VertexInputRate::eVertex;
		bindingDescription[2].binding = 2;
		bindingDescription[2].stride = 3 * sizeof(float);
		bindingDescription[2].inputRate = vk::VertexInputRate::eVertex;

		std::array<vk::VertexInputAttributeDescription, 3> attributeDescriptions;
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[0].offset = 0;
		attributeDescriptions[1].binding = 1;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[1].offset = 0;
		attributeDescriptions[2].binding = 2;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[2].offset = 0;

		vk::PipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = vk::StructureType::ePipelineVertexInputStateCreateInfo;
		vertexInputInfo.flags = vk::PipelineVertexInputStateCreateFlags();
		vertexInputInfo.vertexBindingDescriptionCount = (unsigned)bindingDescription.size();
		vertexInputInfo.vertexAttributeDescriptionCount = (unsigned)attributeDescriptions.size();
		vertexInputInfo.pVertexBindingDescriptions = bindingDescription.data();
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		vk::PipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = vk::StructureType::ePipelineInputAssemblyStateCreateInfo;
		inputAssembly.flags = vk::PipelineInputAssemblyStateCreateFlags();
		inputAssembly.topology = vk::PrimitiveTopology::eTriangleStrip; // vk::PrimitiveTopology::eTriangleList;
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
		rasterizer.polygonMode = vk::PolygonMode::eFill; // vk::PolygonMode::eLine;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = vk::CullModeFlagBits::eBack; // vk::CullModeFlagBits::eNone;
		rasterizer.frontFace = vk::FrontFace::eCounterClockwise; // vk::FrontFace::eClockwise;
		rasterizer.depthBiasEnable = VK_FALSE;
		rasterizer.depthBiasConstantFactor = 0.0f;
		rasterizer.depthBiasClamp = 0.0f;
		rasterizer.depthBiasSlopeFactor = 0.0f;

		vk::SampleMask sampleMask = UINT_MAX; // uint32_t

		vk::PipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = vk::StructureType::ePipelineMultisampleStateCreateInfo;
		multisampling.flags = vk::PipelineMultisampleStateCreateFlags();
		multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;
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


		vk::PipelineDepthStencilStateCreateInfo depthStencilInfo{};
		depthStencilInfo.sType = vk::StructureType::ePipelineDepthStencilStateCreateInfo;
		depthStencilInfo.flags = vk::PipelineDepthStencilStateCreateFlags();
		depthStencilInfo.depthTestEnable = true;
		depthStencilInfo.depthWriteEnable = true; // bool
		depthStencilInfo.depthCompareOp = vk::CompareOp::eLess; // vk::CompareOp::eLessOrEqual;
		depthStencilInfo.depthBoundsTestEnable = false;
		depthStencilInfo.stencilTestEnable = false;
		depthStencilInfo.front = stencilOpState;
		depthStencilInfo.back = stencilOpState;
		depthStencilInfo.maxDepthBounds = 1.0f;
		depthStencilInfo.minDepthBounds = 0.0f;

		vk::PipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
		// vk::ColorComponentFlagBits::eA | vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB;
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
		pipelineInfo.layout = pipelineLayout;
		pipelineInfo.renderPass = RenderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineInfo.basePipelineIndex = -1;

		return vk::raii::Pipeline(Device, pipelineCache, pipelineInfo, nullptr);
	}
} // ns vkcube