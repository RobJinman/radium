#ifndef RADIUM_MODULE_MANAGER_HPP
#define RADIUM_MODULE_MANAGER_HPP


#include <string>
#include <map>
#include "module.hpp"


namespace radium {


class RootModule;

class ModuleManager {
  friend class Radium;
  
  public:
    RootModule* loadModules(const std::string& moduleDir);
    void unloadModules();

    const ModuleSpec& loadModule(const std::string& path);
    void unloadModule(const ModuleSpec& spec);

    //Module& getModule(moduleName_t name);
    void foo();

  private:
    ModuleManager();

    std::map<moduleName_t, Module*> m_modules;
};


}


#endif
