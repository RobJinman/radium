#ifndef RADIUM_MODULE_MANAGER_HPP
#define RADIUM_MODULE_MANAGER_HPP


#include <string>
#include <map>
#include "module.hpp"


namespace radium {


class ModuleManager {
  public:
    static ModuleManager& getInstance();

    ModuleManager();

    void loadModules(const std::string& moduleDir);
    void unloadModules();

    void foo();

    Module& getModule(moduleName_t name);

  private:
    static ModuleManager* instance;
    std::map<moduleName_t, Module*> m_modules;
};


}


#endif
