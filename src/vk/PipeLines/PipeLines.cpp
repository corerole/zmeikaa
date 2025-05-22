#include "PipeLines.hpp"

static std::unique_ptr<vk::raii::PipelineCache> update_PipelineCache(vk::raii::Device& Device) {
    vk::PipelineCacheCreateInfo createInfo{};
    createInfo.sType = vk::StructureType::ePipelineCacheCreateInfo;
    createInfo.pInitialData = nullptr;// data.get_data();
    createInfo.initialDataSize = 0;// data.get_size();

    return std::make_unique<vk::raii::PipelineCache>(Device, createInfo);
}

static std::unique_ptr<vk::raii::PipelineLayout> update_PipelineLayout(vk::raii::Device& Device) {
    vk::PipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = vk::StructureType::ePipelineLayoutCreateInfo;
    return std::make_unique<vk::raii::PipelineLayout>(Device, pipelineLayoutInfo);
}

void App_PipeLines::update_Shaders() {
	StoredVertexID = installShader((readFile(VERTNAME)), Device);
	StoredFragmentID = installShader((readFile(FRAGNAME)), Device);
}

static std::unique_ptr<vk::raii::Pipeline> create_Pipeline(vk::raii::Device& Device,
	vk::raii::ShaderModule& StoredVertexID,
	vk::raii::ShaderModule& StoredFragmentID,
	vk::Extent2D& SwapchainExtent,
	vk::raii::PipelineLayout& PipelineLayout,
	vk::raii::RenderPass& RenderPass,
	vk::raii::PipelineCache& PipelineCache)
{
	vk::PipelineShaderStageCreateInfo vertShaderStageInfo{};
	vertShaderStageInfo.sType = vk::StructureType::ePipelineShaderStageCreateInfo;
	vertShaderStageInfo.stage = vk::ShaderStageFlagBits::eVertex;
	vertShaderStageInfo.module = StoredVertexID;
	vertShaderStageInfo.pSpecializationInfo = nullptr;
	vertShaderStageInfo.pName = "main";

	vk::PipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType = vk::StructureType::ePipelineShaderStageCreateInfo;
	fragShaderStageInfo.stage = vk::ShaderStageFlagBits::eFragment;
	fragShaderStageInfo.module = StoredFragmentID;
	fragShaderStageInfo.pSpecializationInfo = nullptr;
	fragShaderStageInfo.pName = "main";

	vk::PipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	auto bindingDescription = Vertex::getBindingDescription();
	auto attributeDescriptions = Vertex::getAttributeDescriptions();

	vk::PipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = vk::StructureType::ePipelineVertexInputStateCreateInfo;
	vertexInputInfo.flags = vk::PipelineVertexInputStateCreateFlags();
	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.vertexAttributeDescriptionCount = (unsigned)attributeDescriptions.size();
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

	vk::PipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = vk::StructureType::ePipelineInputAssemblyStateCreateInfo;
	inputAssembly.flags = vk::PipelineInputAssemblyStateCreateFlags();
	inputAssembly.topology = vk::PrimitiveTopology::eTriangleList;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	vk::Viewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = SwapchainExtent.width;
	viewport.height = SwapchainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	uint32_t x = 0;
	uint32_t y = 0;
	vk::Offset2D offset(x, y);

	vk::Rect2D scissor{};
	scissor.offset = offset;
	scissor.extent = SwapchainExtent;

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
	rasterizer.polygonMode = vk::PolygonMode::eFill;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = vk::CullModeFlagBits::eNone;
	rasterizer.frontFace = vk::FrontFace::eClockwise;
	rasterizer.depthBiasEnable = VK_FALSE;

	// vk::SampleMask sampleMask = 0; // uint32_t

	vk::PipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType = vk::StructureType::ePipelineMultisampleStateCreateInfo;
	multisampling.flags = vk::PipelineMultisampleStateCreateFlags();
	multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;
	multisampling.sampleShadingEnable = VK_FALSE;
	// multisampling.minSampleShading = 0.0f;
	// multisampling.pSampleMask			= &sampleMask;
	// multisampling.alphaToCoverageEnable = VK_FALSE;
	// multisampling.alphaToOneEnable = VK_FALSE;

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
	colorBlendAttachment.blendEnable = VK_FALSE;
	colorBlendAttachment.srcColorBlendFactor = vk::BlendFactor::eZero;
	colorBlendAttachment.dstColorBlendFactor = vk::BlendFactor::eZero;
	colorBlendAttachment.colorBlendOp = vk::BlendOp::eAdd;
	colorBlendAttachment.srcAlphaBlendFactor = vk::BlendFactor::eZero;
	colorBlendAttachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
	colorBlendAttachment.alphaBlendOp = vk::BlendOp::eAdd;
	colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;

	vk::PipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = vk::StructureType::ePipelineColorBlendStateCreateInfo;		// VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.flags = vk::PipelineColorBlendStateCreateFlags();
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = vk::LogicOp::eCopy;																			// VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	std::array<vk::DynamicState, 2>    dynamicStates = { vk::DynamicState::eViewport, vk::DynamicState::eScissor };

	vk::PipelineDynamicStateCreateInfo pipelineDynamicState{};
	pipelineDynamicState.sType = vk::StructureType::ePipelineDynamicStateCreateInfo;
	pipelineDynamicState.flags = vk::PipelineDynamicStateCreateFlags();
	pipelineDynamicState.dynamicStateCount = (unsigned)dynamicStates.size();
	pipelineDynamicState.pDynamicStates = dynamicStates.data();

	vk::GraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = vk::StructureType::eGraphicsPipelineCreateInfo;
	pipelineInfo.flags = vk::PipelineCreateFlags();
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pTessellationState = nullptr;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = &depthStencilInfo;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = &pipelineDynamicState;
	pipelineInfo.layout = PipelineLayout;
	pipelineInfo.renderPass = RenderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	return std::make_unique<vk::raii::Pipeline>(Device, PipelineCache, pipelineInfo, nullptr);
}


void App_PipeLines::update_Pipeline() {
	update_Shaders();
	PipelineLayout = update_PipelineLayout(Device);
	PipelineCache = update_PipelineCache(Device);
	GraphicsPipeline = create_Pipeline(Device, *StoredVertexID, *StoredFragmentID, SwapchainExtent, *PipelineLayout, RenderPass, *PipelineCache);
}


App_PipeLines::App_PipeLines(   vk::raii::Device        &Device_,
                                vk::Extent2D            &SwapchainExtent_,
                                vk::raii::RenderPass    &RenderPass_) : 
                                Device(Device_),
                                SwapchainExtent(SwapchainExtent_),
                                RenderPass(RenderPass_)
{
    update_Pipeline();
    dbgs << "Pipelines Created!\n";
}

