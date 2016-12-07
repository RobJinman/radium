#ifndef VULKAN_RENDERER_MODULE_HPP
#define VULKAN_RENDERER_MODULE_HPP


#include <renderer_module.hpp>


class VulkanRendererModule : public radium::ModuleV1 {
  public:
    explicit VulkanRendererModule(void* handle)
      : ModuleV1(handle) {}

    static const radium::ModuleV1Spec& spec() {
      static radium::ModuleV1Spec spec = radium::ModuleV1Spec();

      spec.name = "vulkan_renderer";
      spec.author = "Rob Jinman";
      spec.description = "Simple Vulkan renderer";
      spec.version = radium::Version(0, 1);
      spec.minCompatible = radium::Version(0, 1);

      spec.dependencies = radium::dependencyList_t();
      spec.interfaces = &RendererModule::spec();

      return spec;
    }

    virtual void initialise() override;

    virtual const radium::ModuleV1Spec& getSpec() const override {
      return VulkanRendererModule::spec();
    }

    virtual ~VulkanRendererModule() {}
};



#endif
