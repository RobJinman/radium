#ifndef BOULDERDASH_MODULE_HPP
#define BOULDERDASH_MODULE_HPP


#include <renderer_module.hpp>
#include <root_module.hpp>


class BoulderdashModule : public radium::RootModule {
  public:
    explicit BoulderdashModule(void* handle)
      : RootModule(handle) {}

    static const radium::ModuleSpec& spec() {
      static radium::ModuleSpec spec = radium::ModuleSpec();

      spec.isRoot = true;
      spec.name = "boulderdash";
      spec.author = "Rob Jinman";
      spec.description = "The classic game of Boulderdash";
      spec.version = radium::Version(0, 1);
      spec.minCompatible = radium::Version(0, 1);

      spec.dependencies = radium::dependencyList_t({ &RendererModule::spec() });
      spec.interfaces = nullptr;

      return spec;
    }

    virtual void initialise() override;
    virtual void start(radium::Api* api) override;

    virtual const radium::ModuleSpec& getSpec() const override {
      return BoulderdashModule::spec();
    }

    virtual ~BoulderdashModule() {}
};


#endif
