#include <iostream>
#include <dlfcn.h>
#include <dirent.h>
#include <algorithm>
#include <list>
#include "module_manager.hpp"
#include "module_v1.hpp"
#include "exception.hpp"


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


namespace radium {


ModuleManager* ModuleManager::instance = nullptr;

ModuleManager& ModuleManager::getInstance() {
  if (ModuleManager::instance == nullptr) {
    ModuleManager::instance = new ModuleManager();
  }

  return *ModuleManager::instance;
}

static void printModuleInfo(const ModuleV1& module) {
  const ModuleV1Spec& spec = module.getSpec();

  cout << "*===========================================\n";
  cout << "* " << spec.name << " v" << spec.version << " by " << spec.author << "\n";
  cout << "*\n";
  cout << "* " << spec.description << "\n";
  cout << "*===========================================\n";
}

static ModuleV1* loadModuleFromLib(void* handle) {
  typedef void* (*fnInstantiate_t)(void*);

  dlerror();

  fnInstantiate_t fnInstantiate = reinterpret_cast<fnInstantiate_t>(dlsym(handle, "instantiate"));
  DL_CHECK(handle, "Error loading symbol 'instantiate'");

  ModuleV1* module = reinterpret_cast<ModuleV1*>(fnInstantiate(handle));
  printModuleInfo(*module);

  return module;
}

static void destroyModule(ModuleV1* module) {
  typedef void (*fnDestroy_t)(void*);
  void* handle = module->handle();

  dlerror();

  fnDestroy_t fnDestroy = reinterpret_cast<fnDestroy_t>(dlsym(handle, "destroy"));
  DL_CHECK(handle, "Error loading symbol 'destroy'");

  fnDestroy(module);
  dlclose(module->handle());
}

static ModuleV1* loadModuleFromPath(const string& path) {
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

static bool satisfiesDependency_r(const ModuleV1Spec& needed, const ModuleV1Spec* spec) {
  if (needed.name == spec->name
    && needed.version <= spec->version
    && spec->minCompatible <= needed.version) {
      return true;
  }

  const ModuleV1Spec* interfaces = dynamic_cast<const ModuleV1Spec*>(spec->interfaces);
  if (interfaces && satisfiesDependency_r(needed, interfaces)) {
    return true;
  }

  return false;
}

static bool dependencyMet(const ModuleV1Spec& needed, list<ModuleV1*> modules) {
  return any_of(modules.begin(), modules.end(), [&needed](ModuleV1* dep) {
    return satisfiesDependency_r(needed, &dep->getSpec());
  });
}

static bool dependenciesMet(const ModuleV1* module, list<ModuleV1*> modules) {
  const ModuleV1Spec& spec = module->getSpec();

  for (auto dep : spec.dependencies) {
    const ModuleV1Spec* depSpec = dynamic_cast<const ModuleV1Spec*>(dep);

    if (dependencyMet(*depSpec, modules) == false) {
      return false;
    }
  }

  return true;
}

static void initialiseModules(map<moduleName_t, Module*>& modules) {
  for (auto entry : modules) {
    dynamic_cast<ModuleV1*>(entry.second)->initialise();
  }
}

static void startModules(map<moduleName_t, Module*>& modules) {
  for (auto entry : modules) {
    dynamic_cast<ModuleV1*>(entry.second)->start();
  }
}

ModuleManager::ModuleManager() {}

void ModuleManager::foo() {
  std::cout << "ModuleManager::foo()\n";
}

/*
Module& ModuleManager::getModule(moduleName_t name) {
  return *m_modules.at(name);
}*/

const ModuleSpec& ModuleManager::loadModule(const string& path) {
  return loadModuleFromPath(path)->getSpec();
}

void ModuleManager::unloadModule(const ModuleSpec& spec) {
  const ModuleV1Spec& v1spec = dynamic_cast<const ModuleV1Spec&>(spec);
  auto it = m_modules.find(v1spec.name);

  if (it != m_modules.end()) {
    m_modules.erase(it);
    destroyModule(dynamic_cast<ModuleV1*>(it->second));
  }
}

void ModuleManager::loadModules(const string& moduleDir) {
  list<ModuleV1*> modules;
  DIR* dir = opendir(moduleDir.c_str());

  dirent* entity = readdir(dir);
  while (entity) {
    if (entity->d_type == DT_REG) {
      string path = moduleDir + string("/") + entity->d_name;

      ModuleV1* module = loadModuleFromPath(path);

      if (module != nullptr) {
        modules.push_back(module);
      }
    }

    entity = readdir(dir);
  }

  for (auto module : modules) {
    const ModuleV1Spec& spec = module->getSpec();

    if (dependenciesMet(module, modules)) {
      m_modules[spec.name] = module;
    }
    else {
      destroyModule(module);
      EXCEPTION("Could not load module '" << spec.name << "'; Dependencies not met");
    }
  }

  initialiseModules(m_modules);
  startModules(m_modules);
}

void ModuleManager::unloadModules() {
  for (auto entry : m_modules) {
    m_modules.erase(entry.first);
    destroyModule(dynamic_cast<ModuleV1*>(entry.second));
  }
}


}
