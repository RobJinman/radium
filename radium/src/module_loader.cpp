// Implementation of the module_loader class from the module_loader module.


#include "module_loader.hpp"
#include "module_manager.hpp"


using std::string;


namespace radium {


ModuleLoader* ModuleLoader::instance = nullptr;

ModuleLoader& ModuleLoader::getInstance() {
  if (ModuleLoader::instance == nullptr) {
    ModuleLoader::instance = new ModuleLoader();
  }

  return *ModuleLoader::instance;
}

ModuleLoader::ModuleLoader() {}

const ModuleSpec& ModuleLoader::loadModule(const string& path) {
  return ModuleManager::getInstance().loadModule(path);
}

void ModuleLoader::unloadModule(const ModuleSpec& spec) {
  ModuleManager::getInstance().unloadModule(spec);
}

void ModuleLoader::foo() {
  ModuleManager::getInstance().foo();
}


}
