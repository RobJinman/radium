#ifndef GL_RENDERER_HPP
#define GL_RENDERER_HPP


#include <renderer.hpp>


class GlRenderer : public Renderer {
  public:
    GlRenderer()
      : Renderer() {}

    virtual void draw(const Mesh& mesh, const Camera& camera) const override;
};


#endif
