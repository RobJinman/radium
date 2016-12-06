#ifndef RADIUM_MODULE_MANAGER_HPP
#define RADIUM_MODULE_MANAGER_HPP


#include <string>
#include <memory>
#include "module.hpp"


namespace radium {


class ModuleManagerImpl;

class ModuleManager {
  public:
    static ModuleManager& getInstance();

    ModuleManager();

    void loadModules(const std::string& moduleDir);
    void unloadModules();

    Module& getModule(moduleName_t name);

  private:
    static ModuleManager* instance;
    std::unique_ptr<ModuleManagerImpl> m_impl;
};


}


#endif
