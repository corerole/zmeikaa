#include "RenderPass.hpp"

#if 0
App_RenderPass::App_RenderPass( vk::raii::Device& Device_,
																vk::Format &SwapchainImageFormat_) : 
																Device(Device_),
																SwapchainImageFormat(SwapchainImageFormat_)
{
		update_RenderPass();
		dbgs << "Render Pass Created!\n";
}
#endif

namespace vk {
	namespace supp {
		vk::raii::RenderPass get_RenderPass(
			const vk::raii::Device& Device,
			const vk::Format& SwapchainImageFormat
		) {
			vk::AttachmentDescription colorAttachment{};
			// colorAttachment.sType = vk::StructureType::eAttachmentDescription2;
			colorAttachment.flags = vk::AttachmentDescriptionFlags();
			colorAttachment.format = SwapchainImageFormat;
			colorAttachment.samples = vk::SampleCountFlagBits::e1;
			colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
			colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
			colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
			// colorAttachment.initialLayout = vk::ImageLayout::ePresentSrcKHR;
			// We want the image to be ready for presentation using the swap chain after rendering
			colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;
			colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
			colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;

			// Attachment буфера глубины
			vk::AttachmentDescription depthAttachment{};
			depthAttachment.format = vk::Format::eD32Sfloat; // Формат глубины
			depthAttachment.samples = vk::SampleCountFlagBits::e1;
			depthAttachment.loadOp = vk::AttachmentLoadOp::eClear;
			depthAttachment.storeOp = vk::AttachmentStoreOp::eDontCare;
			depthAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
			depthAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
			depthAttachment.initialLayout = vk::ImageLayout::eUndefined;
			depthAttachment.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

			vk::AttachmentReference colorAttachmentRef{};
			// colorAttachmentRef.aspectMask = vk::ImageAspectFlagBits::eNone;
			colorAttachmentRef.attachment = 0;
			colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

			vk::AttachmentReference depthAttachmentRef{};
			depthAttachmentRef.attachment = 1;
			depthAttachmentRef.layout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

			vk::SubpassDescription subpass{};
			//subpass.sType = vk::StructureType::eSubpassDescription2;
			subpass.flags = vk::SubpassDescriptionFlags();
			subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
			subpass.colorAttachmentCount = 1;
			subpass.pColorAttachments = &colorAttachmentRef;
			subpass.pDepthStencilAttachment = &depthAttachmentRef;

			vk::SubpassDependency dependency{};
			//dependency.sType = vk::StructureType::eSubpassDependency2;
			dependency.dependencyFlags = vk::DependencyFlags();
			dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass = 0u;
			dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
			dependency.srcAccessMask = vk::AccessFlagBits::eNone;
			dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
			dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite;

			std::array<vk::AttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };
#if 1
			vk::RenderPassCreateInfo createInfo{};
			// createInfo.sType = vk::StructureType::eRenderPassCreateInfo;
			createInfo.sType = vk::StructureType::eRenderPassCreateInfo;
			createInfo.flags = vk::RenderPassCreateFlags();
			createInfo.pNext = nullptr;
			createInfo.attachmentCount = static_cast<unsigned>(attachments.size());
			createInfo.pAttachments = attachments.data();
			createInfo.subpassCount = 1;
			createInfo.pSubpasses = &subpass;
			createInfo.dependencyCount = 1;
			createInfo.pDependencies = &dependency;
			// createInfo.correlatedViewMaskCount = 0;
			// createInfo.pCorrelatedViewMasks = 0;
#else
			vk::AttachmentDescription colorAttachments[] = { colorAttachment };
			vk::SubpassDescription subpasses[] = { subpass };
			vk::SubpassDependency subpassesDependencies = { dependency };
			vk::RenderPassCreateInfo createInfo(
				vk::RenderPassCreateFlags(),
				colorAttachments,
				subpasses,
				subpassesDependencies
			);
#endif
			return vk::raii::RenderPass(Device, createInfo);
		}
	}
}