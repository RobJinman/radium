#ifndef RADIUM_MODULE_LOADER_HPP
#define RADIUM_MODULE_LOADER_HPP


#include <string>
#include <map>
#include <list>
#include "module.hpp"


namespace radium {


class RootModule;

class ModuleLoader {
  friend class Radium;

  public:
    RootModule* loadModules(const std::string& moduleDir, const std::list<std::string>& libs);
    void unloadModules();

    const ModuleSpec& loadModule(const std::string& path);
    void unloadModule(moduleName_t name);

    void foo();

  private:
    ModuleLoader();

    std::map<moduleName_t, Module*> m_modules;
    RootModule* m_rootModule;
};


}


#endif
