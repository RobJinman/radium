#ifndef RADIUM_MODULE_MANAGER_HPP
#define RADIUM_MODULE_MANAGER_HPP


#include <string>
#include <map>
#include "root_module.hpp"
#include "api.hpp"


namespace radium {


class ModuleManager {
  public:
    static ModuleManager& getInstance();

    void loadModules(const std::string& moduleDir);
    void unloadModules();

    const ModuleSpec& loadModule(const std::string& path);
    void unloadModule(const ModuleSpec& spec);

    //Module& getModule(moduleName_t name);
    void foo();

  private:
    ModuleManager();

    static ModuleManager* instance;

    Api m_api;
    std::map<moduleName_t, Module*> m_modules;
    RootModule* m_rootModule;
};


}


#endif
