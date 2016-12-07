#include <iostream>
#include "module_manager.hpp"
#include "exception.hpp"


using std::cerr;
using namespace radium;


#define MODULE_DIR "modules"


int main() {
  try {
    ModuleManager& moduleManager = ModuleManager::getInstance();

    moduleManager.loadModules(MODULE_DIR);
    moduleManager.unloadModules();
  }
  catch (Exception& ex) {
    cerr << ex.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
