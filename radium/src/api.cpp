#include "api.hpp"
#include "module_manager.hpp"


using std::string;


namespace radium {


Api::Api() {}

const ModuleSpec& Api::loadModule(const string& path) {
  return ModuleManager::getInstance().loadModule(path);
}

void Api::unloadModule(const ModuleSpec& spec) {
  ModuleManager::getInstance().unloadModule(spec);
}

void Api::foo() {
  ModuleManager::getInstance().foo();
}


}
