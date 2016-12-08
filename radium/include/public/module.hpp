#ifndef RADIUM_MODULE_HPP
#define RADIUM_MODULE_HPP


#include <string>
#include <vector>
#include "version.hpp"


namespace radium {


class ModuleSpec;

typedef std::string moduleName_t;
typedef std::vector<const ModuleSpec*> dependencyList_t;


struct ModuleSpec {
  ModuleSpec()
    : isRoot(false),
      interfaces(nullptr) {}

  moduleName_t name;
  std::string author;
  std::string description;
  Version version;
  Version minCompatible;
  bool isRoot;

  dependencyList_t dependencies;
  const ModuleSpec* interfaces;

  int moduleApiVersion() const {
    return 1;
  }

  virtual ~ModuleSpec() {}
};


class Module {
  public:
    explicit Module(void* handle)
      : m_handle(handle) {}


    void* handle() const {
      return m_handle;
    }

    int moduleApiVersion() const {
      return 1;
    }

    virtual const ModuleSpec& getSpec() const = 0;
    virtual void initialise() {}

    virtual ~Module() {}

  private:
    void* m_handle;
};


}


extern "C" int moduleApiVersion();
extern "C" void* instantiate(void* handle);
extern "C" void destroy(void* inst);


#endif
