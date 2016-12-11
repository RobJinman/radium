#include <iostream>
#include <list>
#include "radium.hpp"
#include "module_manager.hpp"
#include "api.hpp"
#include "exception.hpp"
#include "root_module.hpp"
#include "manifest.hpp"


#define MODULE_DIR "modules"


using std::list;
using std::cerr;
using std::string;


int main() {
  radium::Radium radium;
  return radium.start();
}


namespace radium {


int Radium::start() {
  try {
    ModuleManager moduleManager;
    Api api(moduleManager);

    list<string> libs = parseManifestFile("manifest.txt");

    RootModule* root = moduleManager.loadModules(MODULE_DIR, libs);

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
