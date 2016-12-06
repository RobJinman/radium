#ifndef RADIUM_MODULE_MANAGER_IMPL_HPP
#define RADIUM_MODULE_MANAGER_IMPL_HPP


#include <map>
#include "module.hpp"


namespace radium {


class ModuleV1;
class ModuleV2;

class ModuleManagerImpl {
  public:
    void loadModules(const std::string& moduleDir);
    void unloadModules();

    Module& getModule(moduleName_t name);

  private:
    std::map<moduleName_t, Module*> m_modules;
};


}


#endif
