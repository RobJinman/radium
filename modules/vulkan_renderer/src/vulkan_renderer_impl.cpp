#include <iostream>
#include "vulkan_renderer_impl.hpp"
#include "mesh.hpp"
#include "camera.hpp"


VulkanRendererImpl::VulkanRendererImpl()
  : RendererImpl() {

  m_num = 555;
}

void VulkanRendererImpl::draw(const Mesh& mesh, const Camera& camera) const {
  std::cout << "VulkanRendererImpl::draw(), m_num = " << m_num << "\n";
}
