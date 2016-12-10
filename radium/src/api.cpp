#include "api.hpp"
#include "module_manager.hpp"


using std::string;


namespace radium {


Api::Api(ModuleManager& moduleManager)
  : m_moduleManager(moduleManager) {}

const ModuleSpec& Api::loadModule(const string& path) {
  return m_moduleManager.loadModule(path);
}

void Api::unloadModule(moduleName_t name) {
  m_moduleManager.unloadModule(name);
}

void Api::foo() {
  m_moduleManager.foo();
}


}
