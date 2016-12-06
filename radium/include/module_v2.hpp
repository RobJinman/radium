#ifndef RADIUM_MODULE_V2_HPP
#define RADIUM_MODULE_V2_HPP


#include "module_v1.hpp"


namespace radium {


struct ModuleV2Spec : public ModuleSpec {
  ModuleV2Spec()
    : ModuleSpec() {}

  moduleName_t name;
  std::string author;
  std::string description;
  Version version;
  Version minCompatible;

  const ModuleSpec** dependencies;
  const ModuleSpec* interfaces;

  virtual int moduleApiVersion() const override final {
    return 2;
  }

  virtual ~ModuleV2Spec() {}
};


class ModuleV2 : public Module {
  public:
    ModuleV2(void* handle)
      : Module(handle) {}

    virtual int moduleApiVersion() const override final {
      return 2;
    }

    virtual void initialise() = 0;

    virtual ~ModuleV2() {}
};


}


extern "C" int moduleApiVersion();
extern "C" void* instantiate(void* handle);
extern "C" void destroy(void* inst);


#endif
