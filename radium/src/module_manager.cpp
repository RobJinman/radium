#include "module_manager.hpp"
#include "module_manager_impl.hpp"


using std::string;


namespace radium {


ModuleManager* ModuleManager::instance = nullptr;

ModuleManager& ModuleManager::getInstance() {
  if (ModuleManager::instance == nullptr) {
    ModuleManager::instance = new ModuleManager();
  }

  return *ModuleManager::instance;
}

ModuleManager::ModuleManager()
  : m_impl(new ModuleManagerImpl) {}

void ModuleManager::loadModules(const string& moduleDir) {
  m_impl->loadModules(moduleDir);
}

void ModuleManager::unloadModules() {
  m_impl->unloadModules();
}

Module& ModuleManager::getModule(moduleName_t name) {
  return m_impl->getModule(name);
}


}
