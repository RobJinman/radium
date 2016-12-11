#include "api.hpp"
#include "module_loader.hpp"


using std::string;


namespace radium {


Api::Api(ModuleLoader& moduleLoader)
  : m_moduleLoader(moduleLoader) {}

const ModuleSpec& Api::loadModule(const string& path) {
  return m_moduleLoader.loadModule(path);
}

void Api::unloadModule(moduleName_t name) {
  m_moduleLoader.unloadModule(name);
}

void Api::foo() {
  m_moduleLoader.foo();
}


}
