#include "module_manager.hpp"
//#include "bootstrap_module.hpp"
//#include "bootstrap_service.hpp"


using namespace radium;


#define MODULE_DIR "modules"


int main() {
  ModuleManager& moduleManager = ModuleManager::getInstance();
  moduleManager.loadModules(MODULE_DIR);

//  BootstrapService root;
//  root.start();

  moduleManager.unloadModules();

  return EXIT_SUCCESS;
}
