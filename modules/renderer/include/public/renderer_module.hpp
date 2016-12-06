#ifndef RENDERER_MODULE_HPP
#define RENDERER_MODULE_HPP


#include <module_v1.hpp>


class RendererModule : public radium::ModuleV1 {
  public:
    RendererModule(void* handle)
      : ModuleV1(handle) {}

    static const radium::ModuleV1Spec& spec() {
      static radium::ModuleV1Spec spec = radium::ModuleV1Spec();

      spec.name = "renderer";
      spec.author = "Rob Jinman";
      spec.description = "Generic renderer interface";
      spec.version = radium::Version(0, 1);
      spec.minCompatible = radium::Version(0, 1);

      spec.dependencies = radium::dependencyList_t();
      spec.interfaces = nullptr;

      return spec;
    }

    virtual const radium::ModuleV1Spec& getSpec() const override {
      return RendererModule::spec();
    }

    virtual void initialise() override {}

    virtual ~RendererModule() {}
};


#endif
