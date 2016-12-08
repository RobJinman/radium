#ifndef RADIUM_ROOT_MODULE_HPP
#define RADIUM_ROOT_MODULE_HPP


#include "module.hpp"


namespace radium {


class Api;

class RootModule : public Module {
  public:
    RootModule(void* handle)
      : Module(handle) {}

    virtual void start(Api* api) = 0;

    virtual ~RootModule() {}
};


}


#endif
