#ifndef RENDERER_MODULE_HPP
#define RENDERER_MODULE_HPP


#include <module.hpp>


class RendererModule : public radium::Module {
  public:
    explicit RendererModule(void* handle)
      : Module(handle) {}

    static const radium::ModuleSpec& spec() {
      static radium::ModuleSpec spec = radium::ModuleSpec();

      spec.name = "renderer";
      spec.author = "Rob Jinman";
      spec.description = "Generic renderer interface";
      spec.version = radium::Version(0, 1);
      spec.minCompatible = radium::Version(0, 1);

      spec.dependencies = radium::dependencyList_t();
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
