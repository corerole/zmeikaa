#include "RenderPass.hpp"

App_RenderPass::App_RenderPass( vk::raii::Device& Device_,
                                vk::Format &SwapchainImageFormat_) : 
                                Device(Device_),
                                SwapchainImageFormat(SwapchainImageFormat_)
{
    update_RenderPass();
    dbgs << "Render Pass Created!\n";
}

void App_RenderPass::update_RenderPass() {
    vk::AttachmentDescription colorAttachment{};
    // colorAttachment.sType = vk::StructureType::eAttachmentDescription2;
    colorAttachment.flags = vk::AttachmentDescriptionFlags();
    colorAttachment.format = SwapchainImageFormat;
    colorAttachment.samples = vk::SampleCountFlagBits::e1;
    colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
    colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;
    colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
    colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;

    vk::AttachmentReference colorAttachmentRef{};
    // colorAttachmentRef.aspectMask = vk::ImageAspectFlagBits::eNone;
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal; 

    vk::SubpassDescription subpass{};
    //subpass.sType = vk::StructureType::eSubpassDescription2;
    subpass.flags = vk::SubpassDescriptionFlags();
    subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    vk::SubpassDependency dependency{};
    //dependency.sType = vk::StructureType::eSubpassDependency2;
    dependency.dependencyFlags = vk::DependencyFlags();
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput; // VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = vk::AccessFlagBits::eNone;
    dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;

    vk::RenderPassCreateInfo createInfo{};
    // createInfo.sType = vk::StructureType::eRenderPassCreateInfo;
    createInfo.sType = vk::StructureType::eRenderPassCreateInfo;
    createInfo.flags = vk::RenderPassCreateFlags();
    createInfo.pNext = nullptr;
    createInfo.attachmentCount = 1;
    createInfo.pAttachments = &colorAttachment;
    createInfo.subpassCount = 1;
    createInfo.pSubpasses = &subpass;
    createInfo.dependencyCount = 1;
    createInfo.pDependencies = &dependency;
    // createInfo.correlatedViewMaskCount = 0;
    // createInfo.pCorrelatedViewMasks = 0;

    RenderPass.release();
    RenderPass = std::make_unique<vk::raii::RenderPass>(Device, createInfo);
}