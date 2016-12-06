#include <iostream>
#include <renderer.hpp>
#include <camera.hpp>
#include <mesh.hpp>
#include "boulderdash_module.hpp"


using std::cout;


int moduleApiVersion() {
  return 2;
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

  Renderer renderer;
  Camera camera;
  Mesh mesh;

  renderer.draw(mesh, camera);
}
