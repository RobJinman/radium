#ifndef GL_RENDERER_IMPL_HPP
#define GL_RENDERER_IMPL_HPP


#include "renderer_impl.hpp"


class GlRendererImpl : public RendererImpl {
  public:
    GlRendererImpl();

    virtual void draw(const Mesh& mesh, const Camera& camera) const override;

  private:
    int m_num;
};


#endif
