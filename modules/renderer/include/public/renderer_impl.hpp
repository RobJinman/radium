#ifndef RENDERER_IMPL_HPP
#define RENDERER_IMPL_HPP


class Mesh;
class Camera;

class RendererImpl {
  public:
    virtual void draw(const Mesh& mesh, const Camera& camera) const = 0;
};


#endif
