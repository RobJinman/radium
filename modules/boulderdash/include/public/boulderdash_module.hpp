#ifndef BOULDERDASH_MODULE_HPP
#define BOULDERDASH_MODULE_HPP


#include <bootstrap_module.hpp>
#include <renderer_module.hpp>


class BoulderdashModule : public radium::ModuleV2 {
  public:
    BoulderdashModule(void* handle)
      : ModuleV2(handle) {}

    static const radium::ModuleSpec& spec() {
      static radium::ModuleV2Spec spec = radium::ModuleV2Spec();
      static const radium::ModuleSpec* dependencies[] = { &RendererModule::spec() };

      spec.name = "boulderdash";
      spec.author = "Rob Jinman";
      spec.description = "The classic game of Boulderdash";
      spec.version = radium::Version(0, 1);
      spec.minCompatible = radium::Version(0, 1);

      spec.dependencies = dependencies;
      spec.interfaces = &radium::BootstrapModule::spec();

      return spec;
    }

    virtual void initialise() override;

    virtual const radium::ModuleSpec& getSpec() const override {
      return BoulderdashModule::spec();
    }

    virtual ~BoulderdashModule() {}
};



#endif
