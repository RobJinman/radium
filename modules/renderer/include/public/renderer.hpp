#ifndef RENDERER_HPP
#define RENDERER_HPP


#include "mesh.hpp"
#include "camera.hpp"


class Renderer {
  public:
    Renderer() {}

    virtual void draw(const Mesh& mesh, const Camera& camera) const = 0;

    virtual ~Renderer() {}
};


#endif
