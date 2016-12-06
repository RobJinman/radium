#include <iostream>
#include <dlfcn.h>
#include <dirent.h>
#include <algorithm>
#include <list>
#include "module_manager_impl.hpp"
#include "module_v1.hpp"
#include "module_v2.hpp"


#define DL_CHECK(handle, msg) \
  { \
    const char* err = dlerror(); \
    if (err) { \
      std::cerr << msg << "; " << err << "\n"; \
      if (handle) { \
        dlclose(handle); \
      } \
      exit(EXIT_FAILURE); \
    } \
  }


using std::cerr;
using std::cout;
using std::list;
using std::string;


namespace radium {


static void nonFatal(const string& msg) {
  cerr << msg << "\n";
}

Module& ModuleManagerImpl::getModule(moduleName_t name) {
  return *m_modules.at(name);
}

void ModuleManagerImpl::printModuleV1Info(const ModuleV1& module) {
  const ModuleV1Spec& spec = dynamic_cast<const ModuleV1Spec&>(module.getSpec());

  cout << "*===========================================\n";
  cout << "* " << spec.name << " v" << spec.version << " by " << spec.author << "\n";
  cout << "*\n";
  cout << "* " << spec.description << "\n";
  cout << "*===========================================\n";
}

void ModuleManagerImpl::printModuleV2Info(const ModuleV2& module) {
  const ModuleV2Spec& spec = dynamic_cast<const ModuleV2Spec&>(module.getSpec());

  cout << "*===========================================\n";
  cout << "* " << spec.name << " v" << spec.version << " by " << spec.author << "\n";
  cout << "*\n";
  cout << "* " << spec.description << "\n";
  cout << "*===========================================\n";
}

Module* ModuleManagerImpl::loadV1Module(void* handle) {
  typedef void* (*fnInstantiate_t)(void*);
//  typedef void (*fnModuleV1Func_t)(int);

  dlerror();

  fnInstantiate_t fnInstantiate = reinterpret_cast<fnInstantiate_t>(dlsym(handle, "instantiate"));
  DL_CHECK(handle, "Error loading symbol 'instantiate'");

//  fnModuleV1Func_t fnFunc = reinterpret_cast<fnModuleV1Func_t>(dlsym(handle, "moduleV1Func"));
//  DL_CHECK(handle, "Error loading symbol 'instantiate'");

  ModuleV1* module = reinterpret_cast<ModuleV1*>(fnInstantiate(handle));

//  fnFunc(36);

  printModuleV1Info(*module);
  module->initialise();

  return module;
}

void ModuleManagerImpl::unloadV1Module(ModuleV1* module) {
  typedef void (*fnDestroy_t)(void*);
  void* handle = module->handle();

  dlerror();

  fnDestroy_t fnDestroy = reinterpret_cast<fnDestroy_t>(dlsym(handle, "destroy"));
  DL_CHECK(handle, "Error loading symbol 'destroy'");

  fnDestroy(module);
}

Module* ModuleManagerImpl::loadV2Module(void* handle) {
  typedef void* (*fnInstantiate_t)(void*);
//  typedef void (*fnModuleV2Func_t)(int);

  dlerror();

  fnInstantiate_t fnInstantiate = reinterpret_cast<fnInstantiate_t>(dlsym(handle, "instantiate"));
  DL_CHECK(handle, "Error loading symbol 'instantiate'");

//  fnModuleV2Func_t fnFunc = reinterpret_cast<fnModuleV2Func_t>(dlsym(handle, "moduleV2Func"));
//  DL_CHECK(handle, "Error loading symbol 'instantiate'");

  ModuleV2* module = reinterpret_cast<ModuleV2*>(fnInstantiate(handle));

//  fnFunc(47);

  printModuleV2Info(*module);
  module->initialise();

  return module;
}

void ModuleManagerImpl::unloadV2Module(ModuleV2* module) {
  typedef void (*fnDestroy_t)(void*);
  void* handle = module->handle();

  dlerror();

  fnDestroy_t fnDestroy = reinterpret_cast<fnDestroy_t>(dlsym(handle, "destroy"));
  DL_CHECK(handle, "Error loading symbol 'destroy'");

  fnDestroy(module);
}

Module* ModuleManagerImpl::loadModule(const string& path) {
  void* handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
  DL_CHECK(handle, "Error loading module");

  typedef int (*fnModuleApiVersion_t)();

  fnModuleApiVersion_t fnApiVersion = reinterpret_cast<fnModuleApiVersion_t>(dlsym(handle,
    "moduleApiVersion"));
  DL_CHECK(handle, "Error loading symbol 'moduleApiVersion'");

  Module* module = nullptr;

  switch (fnApiVersion()) {
    case 0:
      nonFatal("Error loading module; Module API no longer supported");
      dlclose(handle);
    case 1:
      module = loadV1Module(handle);
      break;
    case 2:
      module = loadV2Module(handle);
      break;
    default:
      nonFatal("Error loading module; Unrecognised API version");
      dlclose(handle);
  }

  return module;
}

bool ModuleManagerImpl::dependencyMet(const ModuleSpec& needed, const ModuleSpec* available) {
  return true; /*
  return any_of(available.begin(), available.end(), [&needed](ModuleDependency dep) {
    return needed.name == dep.name
      && needed.version <= dep.version
      && dep.minCompatible <= needed.version;
  });*/
}

bool ModuleManagerImpl::dependenciesMet(const Module* module, const ModuleSpec* available) {
  /*
  for (auto dep : module->dependencies()) {
    if (dependencyMet(dep, available) == false) {
      return false;
    }
  }*/

  return true;
}

void ModuleManagerImpl::loadModules(const string& moduleDir) {
  ModuleSpec* available; // TODO
  list<Module*> modules;

  DIR* dir = opendir(moduleDir.c_str());

  dirent* entity = readdir(dir);
  while (entity) {
    if (entity->d_type == DT_REG) {
      string path = moduleDir + string("/") + entity->d_name;

      Module* module = loadModule(path);
      const ModuleSpec& spec = module->getSpec();

      //available.insert(spec->dependencies().begin(), spec->dependencies().end());

      modules.push_back(module);
    }

    entity = readdir(dir);
  }

  for (auto module : modules) {
    if (dependenciesMet(module, available)) {
      const ModuleV2Spec& spec = dynamic_cast<const ModuleV2Spec&>(module->getSpec()); // TODO

      m_modules[spec.name] = module;
    }
    else {
      nonFatal("Error loading module; Dependencies not met");
      dlclose(module->handle());
    }
  }
}

void ModuleManagerImpl::unloadModule(moduleName_t name) {
  Module* module = m_modules[name];

  switch (module->moduleApiVersion()) {
    case 1: {
      unloadV1Module(dynamic_cast<ModuleV1*>(module));
      break;
    }
    case 2: {
      unloadV2Module(dynamic_cast<ModuleV2*>(module));
      break;
    }
  }

  m_modules.erase(name);
}

void ModuleManagerImpl::unloadModules() {
  for (auto it : m_modules) {
    unloadModule(it.first);
  }
}


}
