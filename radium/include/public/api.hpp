#ifndef RADIUM_API_HPP
#define RADIUM_API_HPP


#include <string>
#include "module.hpp"


namespace radium {


class ModuleManager;

class Api {
  friend class Radium;

  public:
    const ModuleSpec& loadModule(const std::string& path);
    void unloadModule(moduleName_t name);

    void foo(); // TODO

  private:
    Api(ModuleManager& moduleManager);

    ModuleManager& m_moduleManager;
};


}


#endif
