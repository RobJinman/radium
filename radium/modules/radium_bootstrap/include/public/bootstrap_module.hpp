#ifndef RADIUM_BOOTSTRAP_MODULE_HPP
#define RADIUM_BOOTSTRAP_MODULE_HPP


#include <module_v1.hpp>


namespace radium {


class BootstrapModule : public ModuleV1 {
  public:
    explicit BootstrapModule(void* handle)
      : ModuleV1(handle) {}

    static const ModuleV1Spec& spec() {
      static ModuleV1Spec spec = ModuleV1Spec();

      spec.name = "radium_bootstrap";
      spec.author = "Rob Jinman";
      spec.description = "Root module";
      spec.version = Version(0, 1);
      spec.minCompatible = Version(0, 1);

      spec.dependencies = radium::dependencyList_t();
      spec.interfaces = nullptr;

      return spec;
    }

    virtual const ModuleV1Spec& getSpec() const override {
      return BootstrapModule::spec();
    }

    virtual void initialise() override {}

    virtual ~BootstrapModule() {}
};


}


#endif
