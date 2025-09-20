#include "vkCubeUpdateFunctions.hpp"

namespace vkcube {
#if 1
	void vkCube_update_UBO(
		vkcube::UBO& ubo,
		const vk::Extent2D& extent,
		std::chrono::steady_clock::time_point startTime
	) {
		
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
		float t = elapsed / 10.0f;

		ubo.modelview = glm::mat4(1.0f);
		ubo.modelview = glm::translate(ubo.modelview, glm::vec3(0.0f, 0.0f, -8.0f));
		ubo.modelview = glm::rotate(ubo.modelview, glm::radians(45.0f + (0.25f * t)), glm::vec3(1.0f, 0.0f, 0.0f));
		ubo.modelview = glm::rotate(ubo.modelview, glm::radians(45.0f - (0.5f * t)), glm::vec3(0.0f, 1.0f, 0.0f));
		ubo.modelview = glm::rotate(ubo.modelview, glm::radians(10.0f + (0.15f * t)), glm::vec3(0.0f, 0.0f, 1.0f));

		float aspect = static_cast<float>(extent.width) / static_cast<float>(extent.height);
		// glm::mat4 projection = glm::frustum(-2.8f, 2.8f, -2.8f * aspect, 2.8f * aspect, 6.0f, 10.0f);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
		// projection[1][1] *= -1;

		ubo.modelviewprojection = projection * ubo.modelview;
#if 0
		glm::mat3 normalMatrix = glm::mat3(ubo.modelview);
		for (int i = 0; i < 3; ++i) {
			ubo.normal[i] = glm::vec4(normalMatrix[i], 0.0f);
		}
#endif
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(ubo.modelview)));
		for (int i = 0; i < 3; ++i) {
			ubo.normal[i] = glm::vec4(normalMatrix[i], 0.0f);
		}
	}
#else
	void vkCube_update_UBO(
		vkcube::UBO& ubo,
		const vk::Extent2D& extent,
		std::chrono::steady_clock::time_point startTime
	) {
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
		float t = elapsed / 1000.0f;

		ubo.modelview = glm::mat4(1.0f);
		ubo.modelview = glm::translate(ubo.modelview, glm::vec3(0.0f, 0.0f, -8.0f));
		ubo.modelview = glm::rotate(ubo.modelview, glm::radians(45.0f + (0.25f * t)), glm::vec3(1.0f, 0.0f, 0.0f));
		ubo.modelview = glm::rotate(ubo.modelview, glm::radians(45.0f - (0.5f * t)), glm::vec3(0.0f, 1.0f, 0.0f));
		ubo.modelview = glm::rotate(ubo.modelview, glm::radians(10.0f + (0.15f * t)), glm::vec3(0.0f, 0.0f, 1.0f));

		float aspect = static_cast<float>(extent.width) / static_cast<float>(extent.height);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
		ubo.modelviewprojection = projection * ubo.modelview;

		glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(ubo.modelview)));
		for (int i = 0; i < 3; ++i) {
			ubo.normal[i] = glm::vec4(normalMatrix[i], 0.0f);
		}
	}
#endif

	void vkCube_set_CommandBuffer(
		std::vector<vk::raii::CommandBuffer>& commandBuffers,
		const std::vector<vk::raii::Framebuffer>& framebuffers,
		const vk::raii::RenderPass& renderpass,
		const vk::Rect2D& scissor,
		const vk::Viewport& viewport,
		const void* Data
	) {
		const vkcube::vkCube_CommandBufferData& data = *reinterpret_cast<const vkcube::vkCube_CommandBufferData*>(Data);

		vkcube::UBO ubo;
		vkcube::vkCube_update_UBO(ubo, scissor.extent, data.startTime);

		void* mapped = data.buffer.second.mapMemory(0, sizeof(vkcube::UBO));
		std::memcpy(mapped, &ubo, sizeof(vkcube::UBO));
		data.buffer.second.unmapMemory();

		for (size_t i = 0; i < commandBuffers.size(); ++i) {
			vk::raii::CommandBuffer& commandBuffer = commandBuffers[i];
			const vk::raii::Framebuffer& framebuffer = framebuffers[i];

			// const vk::Buffer buffers[] = { *data.buffer.first, *data.buffer.first, *data.buffer.first };
			vk::CommandBufferBeginInfo cb_begin_info{};
			commandBuffer.begin(cb_begin_info);
			std::array<vk::ClearValue, 2> clearVal{};
			clearVal[0] = vk::ClearColorValue(0.0f, 0.0f, 0.0f, 1.0f);
			clearVal[1] = vk::ClearDepthStencilValue(1.0f, 0);
			vk::RenderPassBeginInfo rr_begin_info(*renderpass, *framebuffer, scissor, clearVal);
			commandBuffer.beginRenderPass(rr_begin_info, vk::SubpassContents::eInline);
			commandBuffer.bindVertexBuffers(0, { data.buffer.first, data.buffer.first, data.buffer.first }, data.offsets);
			commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, *data.pipeline);
			commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *data.pipelineLayout, 0, { *data.descriptorSet }, {});
			commandBuffer.setViewport(0, viewport);
			commandBuffer.setScissor(0, scissor);
			for (int j = 0; j < 6; ++j) {
				commandBuffer.draw(4, 1, j * 4, 0);
			}
			// commandBuffer.draw(36, 1, 0, 0);
			commandBuffer.endRenderPass();
			commandBuffer.end();
		}
	}
} // ns vkcube
