#include <iostream>
#include "gl_renderer_impl.hpp"
#include "mesh.hpp"
#include "camera.hpp"


GlRendererImpl::GlRendererImpl()
  : RendererImpl() {

    m_num = 987;
  }

void GlRendererImpl::draw(const Mesh& mesh, const Camera& camera) const {
  std::cout << "GlRendererImpl::draw(), m_num = " << m_num << "\n";
}
