#ifndef RADIUM_BOOTSTRAP_MODULE_HPP
#define RADIUM_BOOTSTRAP_MODULE_HPP


#include <module_v2.hpp>


namespace radium {


class BootstrapModule : public ModuleV2 {
  public:
    BootstrapModule(void* handle)
      : ModuleV2(handle) {}

    static const ModuleSpec& spec() {
      static ModuleV2Spec spec = ModuleV2Spec();

      spec.name = "radium_bootstrap";
      spec.author = "Rob Jinman";
      spec.description = "Root module";
      spec.version = Version(0, 1);
      spec.minCompatible = Version(0, 1);

      spec.dependencies = nullptr;
      spec.interfaces = nullptr;

      return spec;
    }

    virtual const ModuleSpec& getSpec() const override {
      return BootstrapModule::spec();
    }

    virtual void initialise() override {}

    virtual ~BootstrapModule() {}
};


}


#endif
