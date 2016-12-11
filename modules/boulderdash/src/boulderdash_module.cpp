#include <iostream>
#include <renderer.hpp>
#include <camera.hpp>
#include <mesh.hpp>
#include <api.hpp>
#include "boulderdash_module.hpp"


using std::cin;
using std::cout;


int moduleApiVersion() {
  return 1;
}

void* instantiate(void* handle) {
  cout << "Instantiating boulderdash\n";

  return new BoulderdashModule(handle);
}

void pluginV2Func(int i) {
  cout << "boulderdash, PluginV2Func, i = " << i << "\n";
}

void destroy(void* inst) {
  cout << "Destroying instance of BoulderdashModule\n";
  delete reinterpret_cast<BoulderdashModule*>(inst);
}


void BoulderdashModule::initialise() {
  cout << "BoulderdashModule::initialise()\n";
}

void BoulderdashModule::start(radium::Api* api) {
  cout << "BoulderdashModule::start()\n";

  radium::moduleName_t current = "gl_renderer";

  while (1) {
    cout << "Load gl_renderer (1) or vulkan_renderer (2):";

    char c;
    cin >> c;

    if (c == '1' && current != "gl_renderer") {
      api->loadModule("modules/libgl_renderer.so");
      api->unloadModule("vulkan_renderer");

      current = "gl_renderer";
    }
    else if (c == '2' && current != "vulkan_renderer") {
      api->loadModule("modules/libvulkan_renderer.so");
      api->unloadModule("gl_renderer");

      current = "vulkan_renderer";
    }
    else if (c == 'q') {
      break;
    }

    Renderer renderer;
    Camera camera;
    Mesh mesh;

    renderer.draw(mesh, camera);
  }
}
