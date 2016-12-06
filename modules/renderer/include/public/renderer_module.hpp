#ifndef RENDERER_MODULE_HPP
#define RENDERER_MODULE_HPP


#include <module_v2.hpp>


class RendererModule : public radium::ModuleV2 {
  public:
    RendererModule(void* handle)
      : ModuleV2(handle) {}

    static const radium::ModuleSpec& spec() {
      static radium::ModuleV2Spec spec = radium::ModuleV2Spec();
      static const radium::ModuleSpec* dependencies[] = {};

      spec.name = "renderer";
      spec.author = "Rob Jinman";
      spec.description = "Generic renderer interface";
      spec.version = radium::Version(0, 1);
      spec.minCompatible = radium::Version(0, 1);

      spec.dependencies = dependencies;
      spec.interfaces = nullptr;

      return spec;
    }

    virtual const radium::ModuleSpec& getSpec() const override {
      return RendererModule::spec();
    }

    virtual void initialise() override {}

    virtual ~RendererModule() {}
};


#endif
