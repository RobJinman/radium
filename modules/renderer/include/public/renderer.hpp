#ifndef RENDERER_HPP
#define RENDERER_HPP


#include <memory>
#include "renderer_impl.hpp"


class Mesh;
class Camera;

class Renderer {
  public:
    Renderer()
      : m_impl(Renderer::createImpl()) {}

    void draw(const Mesh& mesh, const Camera& camera) const {
      m_impl->draw(mesh, camera);
    }

  private:
    static RendererImpl* createImpl();

    std::unique_ptr<RendererImpl> m_impl;
};


#endif
