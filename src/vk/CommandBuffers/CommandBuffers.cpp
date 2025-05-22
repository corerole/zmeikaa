#include "CommandBuffers.hpp"

void App_CommandBuffers::update_CommandBuffers() {
	CommandBuffers.clear();
	unsigned NFrameBufs = (unsigned)SwapchainFramebuffers.size();
	dbgs << "Number of command buffers: " << NFrameBufs << std::endl;

	vk::CommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
	allocInfo.commandPool = CommandPool;
	allocInfo.level = vk::CommandBufferLevel::ePrimary;
	allocInfo.commandBufferCount = NFrameBufs;

	CommandBuffers = Device.allocateCommandBuffers(allocInfo);

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

	vk::Viewport viewports[] = { viewport };
	vk::Rect2D scissors[]  = { scissor };

	for (unsigned i = 0; i < CommandBuffers.size(); ++i) {
		vk::CommandBufferBeginInfo beginInfo{};
		beginInfo.sType = vk::StructureType::eCommandBufferBeginInfo;
		CommandBuffers[i].begin(beginInfo);

		vk::ClearValue clearColor = { {0.2f, 0.3f, 0.3f, 1.0f} };

		vk::RenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = vk::StructureType::eRenderPassBeginInfo;
		renderPassInfo.renderPass = RenderPass;
		renderPassInfo.framebuffer = SwapchainFramebuffers[i];
		renderPassInfo.renderArea.offset = vk::Offset2D(0, 0);
		renderPassInfo.renderArea.extent = SwapchainExtent;
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		CommandBuffers[i].beginRenderPass(renderPassInfo, vk::SubpassContents::eInline);
		CommandBuffers[i].bindPipeline(vk::PipelineBindPoint::eGraphics, Pipeline);
		vk::Buffer vertexBuffers[] = { VertexBuffer };
		VkDeviceSize offsets[] = { 0 };
		CommandBuffers[i].bindVertexBuffers(0, vertexBuffers, offsets);
		CommandBuffers[i].bindIndexBuffer(IndexBuffer, 0, vk::IndexType::eUint16);
		CommandBuffers[i].setViewport(0, viewports);
		CommandBuffers[i].setScissor(0, scissors);
		CommandBuffers[i].drawIndexed(((uint32_t)Indices.size()), 1, 0, 0, 0);
		CommandBuffers[i].endRenderPass();
		CommandBuffers[i].end();
	}
}