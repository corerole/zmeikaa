#ifndef APP_BUFFERS
#define APP_BUFFERS

// #include "../Shaders/Shaders.h"

#include <vulkan/vulkan_raii.hpp>
#include "../../trash/dbg.h"
#include "../Vertex/Vertex.h"
#include <memory>

struct App_Buffers {
	private:
		std::unique_ptr<vk::raii::Buffer>					VertexBuffer;
		std::unique_ptr<vk::raii::DeviceMemory>		VertexBufferMemory;
		std::unique_ptr<vk::raii::Buffer>					IndicesBuffer;
		std::unique_ptr<vk::raii::DeviceMemory>		IndicesBufferMemory;
	private:
		bool																			DevicemapMemory2;
		vk::raii::Device													&Device;
		vk::raii::PhysicalDevice									&PhysDevice;
		vk::raii::CommandPool											&CommandPool;
		vk::raii::Queue														&GraphicsQueue;
	private:
		const std::vector<Vertex>									&Vertices;
		const std::vector<unsigned short>					&Indices;
#if 0
	private:
		void	createBuffer	(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void	copyBuffer		(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
#endif
	public:
		void	create_buffers();
	public:
		
		App_Buffers(vk::raii::Device					&Device_,
								vk::raii::PhysicalDevice	&PhysDevice_,
								vk::raii::CommandPool			&CommandPool_,
								vk::raii::Queue						&GraphicsQueue_,
								bool											d2, 
								const std::vector<Vertex>				&Vertices_,
								const std::vector<unsigned short>	&Indices_) : 
								DevicemapMemory2(d2),
								Device(Device_),
								PhysDevice(PhysDevice_),
								CommandPool(CommandPool_),
								GraphicsQueue(GraphicsQueue_),
								Vertices(Vertices_),
								Indices(Indices_)
		{
			create_buffers();
		};

		vk::raii::Buffer& get_VertexBuffer() { return *VertexBuffer; }
		vk::raii::Buffer& get_IndexBuffer() { return *IndicesBuffer; }
		// std::vector<unsigned short>* get_Indices() { return &Indices; }
};

#endif