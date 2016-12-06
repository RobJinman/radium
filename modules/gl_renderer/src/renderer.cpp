#include "renderer.hpp"
#include "gl_renderer_impl.hpp"


RendererImpl* Renderer::createImpl() {
  return new GlRendererImpl();
}
