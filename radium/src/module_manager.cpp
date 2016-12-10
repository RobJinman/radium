#include <iostream>
#include <dlfcn.h>
#include <dirent.h>
#include <algorithm>
#include <list>
#include "module_manager.hpp"
#include "exception.hpp"
#include "root_module.hpp"


#define DL_CHECK(handle, msg) \
  { \
    const char* err = dlerror(); \
    if (err) { \
      if (handle) { \
        dlclose(handle); \
      } \
      EXCEPTION(msg << "; " << err) \
    } \
  }


using std::cout;
using std::list;
using std::map;
using std::string;
using std::pair;
using std::set;


namespace radium {


//=============================================
// printModuleInfo
//=============================================
static void printModuleInfo(const Module& module) {
  const ModuleSpec& spec = module.getSpec();

  cout << "*===========================================\n";
  cout << "* " << spec.name << " v" << spec.version << " by " << spec.author << "\n";
  cout << "*\n";
  cout << "* " << spec.description << "\n";
  cout << "*===========================================\n";
}

//=============================================
// loadModuleFromLib
//=============================================
static Module* loadModuleFromLib(void* handle) {
  typedef void* (*fnInstantiate_t)(void*);

  dlerror();

  fnInstantiate_t fnInstantiate = reinterpret_cast<fnInstantiate_t>(dlsym(handle, "instantiate"));
  DL_CHECK(handle, "Error loading symbol 'instantiate'");

  Module* module = reinterpret_cast<Module*>(fnInstantiate(handle));
  printModuleInfo(*module);

  return module;
}

//=============================================
// destroyModule
//=============================================
static void destroyModule(Module* module) {
  typedef void (*fnDestroy_t)(void*);
  void* handle = module->handle();

  dlerror();

  fnDestroy_t fnDestroy = reinterpret_cast<fnDestroy_t>(dlsym(handle, "destroy"));
  DL_CHECK(handle, "Error loading symbol 'destroy'");

  fnDestroy(module);
  dlclose(module->handle());
}

//=============================================
// loadModuleFromPath
//=============================================
static Module* loadModuleFromPath(const string& path) {
  dlerror();

  void* handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
  DL_CHECK(handle, "Error loading module");

  typedef int (*fnModuleApiVersion_t)();

  fnModuleApiVersion_t fnApiVersion = reinterpret_cast<fnModuleApiVersion_t>(dlsym(handle,
    "moduleApiVersion"));
  DL_CHECK(handle, "Error loading symbol 'moduleApiVersion'");

  if (fnApiVersion() != 1) {
    dlclose(handle);
    EXCEPTION("Error loading module '" << path << "'; Unrecognised API version");
  }

  return loadModuleFromLib(handle);
}

//=============================================
// satisfiesDependency_r
//=============================================
static bool satisfiesDependency_r(const ModuleSpec& needed, const ModuleSpec& spec) {
  if (needed.name == spec.name
    && needed.version <= spec.version
    && spec.minCompatible <= needed.version) {
      return true;
  }

  if (spec.interfaces && satisfiesDependency_r(needed, *spec.interfaces)) {
    return true;
  }

  return false;
}

//=============================================
// dependencyMet
//=============================================
static bool dependencyMet(const ModuleSpec& needed, const map<moduleName_t, Module*>& modules) {
  return any_of(modules.begin(), modules.end(), [&needed](pair<moduleName_t, Module*> dep) {
    return satisfiesDependency_r(needed, dep.second->getSpec());
  });
}

//=============================================
// dependenciesMet
//=============================================
static bool dependenciesMet(const Module* module, const map<moduleName_t, Module*>& modules) {
  const ModuleSpec& spec = module->getSpec();

  for (auto dep : spec.dependencies) {
    if (dependencyMet(*dep, modules) == false) {
      return false;
    }
  }

  return true;
}

//=============================================
// initialiseModules
//=============================================
static void initialiseModules(map<moduleName_t, Module*>& modules) {
  for (auto entry : modules) {
    entry.second->initialise();
  }
}

//=============================================
// ModuleManager::ModuleManager
//=============================================
ModuleManager::ModuleManager() {}

//=============================================
// ModuleManager::foo
//=============================================
void ModuleManager::foo() {
  std::cout << "ModuleManager::foo()\n";
}

//=============================================
// ModuleManager::loadModule
//
// Load and initialise module. Throw exception if dependencies are not met.
//=============================================
const ModuleSpec& ModuleManager::loadModule(const string& path) {
  Module* module = loadModuleFromPath(path);
  const ModuleSpec& spec = module->getSpec();

  if (m_modules.count(spec.name)) {
    EXCEPTION("Module with name '" << spec.name << "' already loaded");
  }

  if (dependenciesMet(module, m_modules)) {
    m_modules[spec.name] = module;
  }
  else {
    destroyModule(module);
    EXCEPTION("Could not load module '" << spec.name << "'; Dependencies not met");
  }

  module->initialise();

  return spec;
}

//=============================================
// ModuleManager::loadModules
//
// Load modules from the given directory. Throw exception if dependencies aren't met.
//=============================================
RootModule* ModuleManager::loadModules(const string& moduleDir, const set<moduleName_t>& names) {
  RootModule* rootModule = nullptr;
  DIR* dir = opendir(moduleDir.c_str());

  dirent* entity = readdir(dir);
  while (entity) {
    if (entity->d_type == DT_REG) {
      string path = moduleDir + string("/") + entity->d_name;

      Module* module = loadModuleFromPath(path);
      const ModuleSpec& spec = module->getSpec();

      if (m_modules.count(spec.name)) {
        destroyModule(module);
        EXCEPTION("Module with name '" << spec.name << "' already loaded");
      }

      if (module->getSpec().isRoot) {
        rootModule = dynamic_cast<RootModule*>(module);
      }

      m_modules[spec.name] = module;
    }

    entity = readdir(dir);
  }

  for (auto entry : m_modules) {
    Module* module = entry.second;
    const ModuleSpec& spec = module->getSpec();

    if (!dependenciesMet(module, m_modules)) {
      unloadModule(spec.name);
      EXCEPTION("Could not load module '" << spec.name << "'; Dependencies not met");
    }
  }

  initialiseModules(m_modules);

  return rootModule;
}

//=============================================
// ModuleManager::unloadModule
//=============================================
void ModuleManager::unloadModule(moduleName_t name) {
  auto it = m_modules.find(name);

  if (it != m_modules.end()) {
    m_modules.erase(it);
    destroyModule(it->second);
  }
}

//=============================================
// ModuleManager::unloadModules
//=============================================
void ModuleManager::unloadModules() {
  for (auto entry : m_modules) {
    m_modules.erase(entry.first);
    destroyModule(entry.second);
  }
}


}
