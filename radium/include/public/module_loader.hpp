#ifndef RADIUM_MODULE_LOADER
#define RADIUM_MODULE_LOADER


#include "module.hpp"


namespace radium {


class ModuleLoader {
  public:
    static ModuleLoader& getInstance();

    const ModuleSpec& loadModule(const std::string& path);
    void unloadModule(const ModuleSpec& module);

    void foo(); // TODO

  private:
    ModuleLoader();

    static ModuleLoader* instance;
};


}


#endif
