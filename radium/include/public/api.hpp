#ifndef RADIUM_API_HPP
#define RADIUM_API_HPP


#include <string>


namespace radium {


class ModuleSpec;

class Api {
  friend class ModuleManager;

  public:
    const ModuleSpec& loadModule(const std::string& path);
    void unloadModule(const ModuleSpec& module);

    void foo(); // TODO

  private:
    Api();
};


}


#endif
