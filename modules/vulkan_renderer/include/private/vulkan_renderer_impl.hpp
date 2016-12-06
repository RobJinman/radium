#ifndef VULKAN_RENDERER_IMPL_HPP
#define VULKAN_RENDERER_IMPL_HPP


#include "renderer_impl.hpp"


class VulkanRendererImpl : public RendererImpl {
  public:
    VulkanRendererImpl();

    virtual void draw(const Mesh& mesh, const Camera& camera) const override;

  private:
    int m_num;
};


#endif
