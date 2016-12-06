#ifndef GL_RENDERER_MODULE_HPP
#define GL_RENDERER_MODULE_HPP


#include <module_v2.hpp>
#include <renderer_module.hpp>


class GlRendererModule : public radium::ModuleV2 {
  public:
    GlRendererModule(void* handle)
      : ModuleV2(handle) {}

    static const radium::ModuleSpec& spec() {
      static radium::ModuleV2Spec spec = radium::ModuleV2Spec();

      spec.name = "gl_renderer";
      spec.author = "Rob Jinman";
      spec.description = "Simple OpenGL renderer";
      spec.version = radium::Version(0, 1);
      spec.minCompatible = radium::Version(0, 1);

      spec.dependencies = nullptr;
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
