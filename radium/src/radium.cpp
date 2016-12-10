#include <iostream>
#include <set>
#include "radium.hpp"
#include "module_manager.hpp"
#include "api.hpp"
#include "exception.hpp"
#include "root_module.hpp"


#define MODULE_DIR "modules"


using std::set;
using std::cerr;


int main() {
  radium::Radium radium;
  return radium.start();
}


namespace radium {


int Radium::start() {
  try {
    ModuleManager moduleManager;
    Api api(moduleManager);

    set<moduleName_t> names;

    RootModule* root = moduleManager.loadModules(MODULE_DIR, names);

    if (root != nullptr) {
      root->start(&api);
    }

    moduleManager.unloadModules();
  }
  catch (Exception& ex) {
    cerr << ex.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}


}
