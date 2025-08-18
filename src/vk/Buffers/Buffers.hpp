#ifndef APP_BUFFERS
#define APP_BUFFERS

// #include "../Shaders/Shaders.h"

#include <vulkan/vulkan_raii.hpp>
#include "../../trash/dbg.h"
#include "../Vertex/Vertex.h"
#include <memory>

#if 1
struct App_Buffers {
	private:
		std::unique_ptr<vk::raii::Buffer> VertexBuffer;
		std::unique_ptr<vk::raii::DeviceMemory> VertexBufferMemory;
		std::unique_ptr<vk::raii::Buffer> IndicesBuffer;
		std::unique_ptr<vk::raii::DeviceMemory> IndicesBufferMemory;
	private:
		bool DeviceMapMemory2;
	private:
		void get_Buffers(
			const vk::raii::Device& Device,
			const vk::raii::PhysicalDevice& PhysDevice,
			const std::vector<Vertex>& Vertices,
			const std::vector<unsigned short>& Indices,
			const vk::raii::CommandPool& CommandPool,
			const vk::raii::Queue& GraphicsQueue
		);
	public:
		App_Buffers(
			vk::raii::Device& device,
			vk::raii::PhysicalDevice& physical_device,
			vk::raii::CommandPool& commandpool,
			vk::raii::Queue& graphics_queue,
			bool d2, 
			const std::vector<Vertex>	&Vertices,
			const std::vector<unsigned short>	&Indices) 
			:
			DeviceMapMemory2(d2)
		{
			get_Buffers(
				device,
				physical_device,
				Vertices,
				Indices,
				commandpool,
				graphics_queue
			);
		};

		vk::raii::Buffer& get_VertexBuffer() { return *VertexBuffer; }
		const vk::raii::Buffer& get_VertexBuffer() const { return *VertexBuffer; }
		vk::raii::Buffer& get_IndexBuffer() { return *IndicesBuffer; }
		const vk::raii::Buffer& get_IndexBuffer() const { return *IndicesBuffer; }
};
#endif

#endif