#ifndef GL_RENDERER_MODULE_HPP
#define GL_RENDERER_MODULE_HPP


#include <renderer_module.hpp>


class GlRendererModule : public radium::Module {
  public:
    explicit GlRendererModule(void* handle)
      : Module(handle) {}

    static const radium::ModuleSpec& spec() {
      static radium::ModuleSpec spec = radium::ModuleSpec();

      spec.name = "gl_renderer";
      spec.author = "Rob Jinman";
      spec.description = "Simple OpenGL renderer";
      spec.version = radium::Version(0, 1);
      spec.minCompatible = radium::Version(0, 1);

      spec.dependencies = radium::dependencyList_t();
      spec.interfaces = &RendererModule::spec();

      return spec;
    }

    virtual void initialise() override;

    virtual const radium::ModuleSpec& getSpec() const override {
      return GlRendererModule::spec();
    }

    virtual ~GlRendererModule() {}
};


#endif
