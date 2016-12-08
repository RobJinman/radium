#ifndef RADIUM_API_HPP
#define RADIUM_API_HPP


#include <string>


namespace radium {


class ModuleSpec;
class ModuleManager;

class Api {
  friend class Radium;

  public:
    const ModuleSpec& loadModule(const std::string& path);
    void unloadModule(const ModuleSpec& module);

    void foo(); // TODO

  private:
    Api(ModuleManager& moduleManager);

    ModuleManager& m_moduleManager;
};


}


#endif
