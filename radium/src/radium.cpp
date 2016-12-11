#include <iostream>
#include <list>
#include "radium.hpp"
#include "module_loader.hpp"
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
    ModuleLoader moduleLoader;
    Api api(moduleLoader);

    list<string> libs = parseManifestFile("manifest.txt");

    RootModule* root = moduleLoader.loadModules(MODULE_DIR, libs);

    if (root != nullptr) {
      root->start(&api);
    }

    moduleLoader.unloadModules();
  }
  catch (Exception& ex) {
    cerr << ex.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}


}
