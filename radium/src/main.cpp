#include <iostream>
#include "module_manager.hpp"
#include "exception.hpp"
//#include "bootstrap_module.hpp"
//#include "bootstrap_service.hpp"


using std::cerr;
using namespace radium;


#define MODULE_DIR "modules"


int main() {
  try {
    ModuleManager& moduleManager = ModuleManager::getInstance();
    moduleManager.loadModules(MODULE_DIR);

  //  BootstrapService root;
  //  root.start();

    moduleManager.unloadModules();
  }
  catch (Exception& ex) {
    cerr << ex.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
