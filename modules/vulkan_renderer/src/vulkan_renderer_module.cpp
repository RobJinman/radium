#include <iostream>
#include "vulkan_renderer_module.hpp"


using std::cout;


int moduleApiVersion() {
  return 1;
}

void* instantiate(void* handle) {
  cout << "Instantiating vulkan_renderer_module\n";

  return new VulkanRendererModule(handle);
}

void pluginV2Func(int i) {
  cout << "vulkan_renderer_module, PluginV2Func, i = " << i << "\n";
}

void destroy(void* inst) {
  cout << "Destroying instance of VulkanRendererModule\n";
  delete reinterpret_cast<VulkanRendererModule*>(inst);
}


void VulkanRendererModule::initialise() {
  cout << "VulkanRendererModule::initialise()\n";
}
