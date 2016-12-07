#ifndef BOULDERDASH_MODULE_HPP
#define BOULDERDASH_MODULE_HPP


#include <bootstrap_module.hpp>
#include <renderer_module.hpp>


class BoulderdashModule : public radium::ModuleV1 {
  public:
    explicit BoulderdashModule(void* handle)
      : ModuleV1(handle) {}

    static const radium::ModuleV1Spec& spec() {
      static radium::ModuleV1Spec spec = radium::ModuleV1Spec();

      spec.name = "boulderdash";
      spec.author = "Rob Jinman";
      spec.description = "The classic game of Boulderdash";
      spec.version = radium::Version(0, 1);
      spec.minCompatible = radium::Version(0, 1);

      spec.dependencies = radium::dependencyList_t({ &RendererModule::spec() });
      spec.interfaces = &radium::BootstrapModule::spec();

      return spec;
    }

    virtual void initialise() override;

    virtual const radium::ModuleV1Spec& getSpec() const override {
      return BoulderdashModule::spec();
    }

    virtual ~BoulderdashModule() {}
};



#endif
