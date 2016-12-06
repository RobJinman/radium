#include "renderer.hpp"
#include "vulkan_renderer_impl.hpp"


RendererImpl* Renderer::createImpl() {
  return new VulkanRendererImpl();
}
