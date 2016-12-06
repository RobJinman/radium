#ifndef RADIUM_MODULE_V1_HPP
#define RADIUM_MODULE_V1_HPP


#include "module.hpp"
#include "version.hpp"


namespace radium {


struct ModuleV1Spec : public ModuleSpec {
  ModuleV1Spec()
    : ModuleSpec() {}

  moduleName_t name;
  std::string author;
  std::string description;
  Version version;
  Version minCompatible;

  const ModuleSpec** dependencies;
  const ModuleSpec* interfaces;

  virtual int moduleApiVersion() const override final {
    return 1;
  }

  virtual ~ModuleV1Spec() {}
};


class ModuleV1 : public Module {
  public:
    ModuleV1(void* handle)
      : Module(handle) {}

    virtual int moduleApiVersion() const override final {
      return 1;
    }

    virtual void initialise() = 0;

    virtual ~ModuleV1() {}
};


}


extern "C" int moduleApiVersion();
extern "C" void* instantiate(void* handle);
extern "C" void destroy(void* inst);


#endif
