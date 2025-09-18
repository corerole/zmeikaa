#include "vkCubeBuffer.hpp"
// , std::array<vk::DeviceMemory, 3> offsets

namespace vkcube {
	std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_Buffers_vkCube(vk::supp::BufferCreater& bc) {
		auto vVsize = vectorsizeof(vVertices);
		auto vCsize = vectorsizeof(vColors);
		auto vNsize = vectorsizeof(vNormals);
		auto vertex_offset = sizeof(vkcube::UBO);
		auto colors_offset = vertex_offset + vVsize;
		auto normals_offset = colors_offset + vCsize;
		size_t bufferSize = normals_offset + vNsize;
		auto bnm = bc.createEmptyBuffer(
			bufferSize,
			vk::BufferUsageFlagBits::eUniformBuffer | vk::BufferUsageFlagBits::eVertexBuffer,
			vk::MemoryPropertyFlagBits::eHostVisible |vk::MemoryPropertyFlagBits::eHostCoherent
		);
		{
			auto mm = bc.get_MemoryMapper(bnm.second, bufferSize);
			void* mapped = mm.get_mapped();

			std::copy(vVertices.begin(), vVertices.end(), static_cast<decltype(vVertices)::value_type*>((void*)((char*)mapped + vertex_offset) ));
			// std::memcpy((char*)mapped + vertex_offset, vVertices.data(), vVsize);
			std::copy(vColors.begin(), vColors.end(), static_cast<decltype(vColors)::value_type*>((void*)((char*)mapped + colors_offset)));
			//std::memcpy((char*)mapped + colors_offset, vColors.data(), vCsize);
			std::copy(vNormals.begin(), vNormals.end(), static_cast<decltype(vNormals)::value_type*>((void*)((char*)mapped + normals_offset)));
			// std::memcpy((char*)mapped + normals_offset, vNormals.data(), vNsize);
		}
		return bnm;
	}
}