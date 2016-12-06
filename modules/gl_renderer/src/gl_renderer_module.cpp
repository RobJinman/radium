#include <iostream>
#include "gl_renderer_module.hpp"


using std::cout;


int moduleApiVersion() {
  return 1;
}

void* instantiate(void* handle) {
  cout << "Instantiating gl_renderer_module\n";

  return new GlRendererModule(handle);
}

void pluginV2Func(int i) {
  cout << "gl_renderer_module, PluginV2Func, i = " << i << "\n";
}

void destroy(void* inst) {
  cout << "Destroying instance of GlRendererModule\n";
  delete reinterpret_cast<GlRendererModule*>(inst);
}


void GlRendererModule::initialise() {
  cout << "GlRendererModule::initialise()\n";
}
