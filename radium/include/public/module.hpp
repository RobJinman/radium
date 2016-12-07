#ifndef RADIUM_MODULE_HPP
#define RADIUM_MODULE_HPP


#include <string>


namespace radium {


typedef std::string moduleName_t;


struct ModuleSpec {
  virtual int moduleApiVersion() const = 0;
};


class Module {
  public:
    explicit Module(void* handle)
      : m_handle(handle) {}

    virtual const ModuleSpec& getSpec() const = 0;

    void* handle() const {
      return m_handle;
    }

    virtual int moduleApiVersion() const = 0;

  private:
    void* m_handle;
};


}


#endif
