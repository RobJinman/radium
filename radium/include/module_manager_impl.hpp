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

    void printModuleV1Info(const ModuleV1& module);
    void printModuleV2Info(const ModuleV2& module);

    Module* loadV1Module(void* handle);
    void unloadV1Module(ModuleV1* module);

    Module* loadV2Module(void* handle);
    void unloadV2Module(ModuleV2* module);

    Module* loadModule(const std::string& path);
    void unloadModule(moduleName_t name);

    bool dependencyMet(const ModuleSpec& needed, const ModuleSpec* available);
    bool dependenciesMet(const Module* module, const ModuleSpec* available);
};


}


#endif
