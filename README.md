Radium
======

Overview
--------

Radium is a C++ plugin system.

You develop your application as a loose bag of modules, which are loaded into the tiny radium executable at runtime.


Description
-----------

A module is a shared library that implements the following functions.

    extern "C" int moduleApiVersion();
    extern "C" void* instantiate(void* handle);
    extern "C" void destroy(void* inst);

The library should override the Module class and provide an instance of it via the instantiate function above.

The getSpec() function should return a ModuleSpec and make the same ModuleSpec object available via a static spec() method.

    #include <renderer_module.hpp>
    #include <xml_module.hpp>


    class GlRendererModule : public radium::Module {
      public:
        explicit GlRendererModule(void* handle)
          : Module(handle) {}

        static const radium::ModuleSpec& spec() {
          static radium::ModuleSpec spec = radium::ModuleSpec();

          spec.name = "gl_renderer";
          spec.author = "Rob Jinman";
          spec.description = "Simple OpenGL renderer";
          spec.version = radium::Version(0, 1);
          spec.minCompatible = radium::Version(0, 1);

          spec.dependencies = radium::dependencyList_t({ &XmlModule::spec() });
          spec.interfaces = &RendererModule::spec();

          return spec;
        }

        virtual void initialise() override;

        virtual const radium::ModuleSpec& getSpec() const override {
          return GlRendererModule::spec();
        }

        virtual ~GlRendererModule() {}
    };

Beyond overriding the Module class, your module can just be written like any other library - as a collection of header files and a compiled binary. The headers should be separated into a public folder and a private folder. Dependent modules will then include the public headers and declare their dependency on the module in their spec, relying on radium to resolve the dependencies to make the symbols available when needed.

A module can implement the interface of another module. If module B implements the interface of module A, any module that depends on module A can have its dependency satisfied by module B. This would make module A and module B interchangeable.

The interface is a pointer to the spec of another module and so forms a linked list. By default, interface is NULL indicating that the module implements its own interface only.

If module A's spec points to module B's spec then module A must define all the symbols (implement all classes, etc.) located under module B's include/public folder.

It will often be desirable to write an interface-only module to serve as the common interface for a collection of interchangeable implementation modules. Such a module would provide a ModuleSpec as usual and consist entirely of headers, with no binary component. An interface-only module would be distributed to other module developers rather than to the end-user.

What follows is the dependency graph of an example application. Graphs like this appear frequently throughout the documentation. They are created with the aid of [a python script](https://github.com/RobJinman/radium-depvis).

    network*=1.14.7;; \
    /;; \
    /event_queue=3.12.9;; \
    /collision=2.4.4;;event_queue=3.12.4 \
    /udp_network=1.3.8;network*=1.14.7;event_queue=3.12.1 \
    /fun_game=1.2.3;;collision=2.4.0,network*=1.14.5

    network* 1.14.7    ─────────▴1.14.7────▴1.14.5─
                                │          ║       
    event_queue 3.12.9 ─▴3.12.4─│─▴3.12.1──║───────
    collision 2.4.4    ─╨───────│─║─▴2.4.0─║───────
    udp_network 1.3.8  ─────────┴─╨─║──────║───────
    fun_game 1.2.3     ─────────────╨──────╨───────

    KEY
    * interface-only module
    │ implements
    ║ depends on

Above the blank line (marked with asterisks) are the interface-only modules. They are incorporated into the application via the concrete modules that implement them. Concrete modules are shown beneath the blank line.

For the example application above, the end-user distribution will comprise the following artifacts:

- The radium executable
- libevent_queue3.12.9
- libcollision2.4.4
- libudp_network1.3.8
- libfun_game1.2.3
- manifest.txt listing the modules to be loaded at startup
- Any additional config/data files required by the modules


## Example Applications

### An application consisting of a single module

    fun_game spec
        isRoot: true
        name: "fun_game"
        version: "1.2.3"
        minCompatible: "1.2.0"
        dependencies: []
        interface: NULL

    radium_bootstrap*=1.1.2;; \
    /fun_game=1.2.3;radium_bootstrap*=1.1.2;


Compile with headers:

- radium/include
- fun_game/include/public/
- fun_game/include/private/


Can be replaced with:

    better_game spec
        name: "better_game"
        version: "0.6.2"
        minCompatible: "0.6.0"
        dependencies: []
        interface: NULL


### An application consisting of a single module with dependencies on some official modules

    fun_game spec
        isRoot: true
        name: "fun_game"
        version: "1.2.3"
        minCompatible: "1.2.0"
        dependencies: ["gui_base 1.2.2", "audio 1.6.0"]
        interface: NULL

    audio*=1.6.0;; \
    /gui_base=1.2.2;; \
    /fun_game=1.2.3;;audio*=1.6.0,gui_base=1.2.2

    audio* 1.6.0   ─▴1.6.0───
    gui_base 1.2.2 ─║─▴1.2.2─
    fun_game 1.2.3 ─╨─╨──────


Compile with headers:

- fun_game/include/public/
- fun_game/include/private/
- gui_base/include/public/
- audio/include/public/


### An application consisting of two modules

    gl_renderer spec
        isRoot: false
        name: "gl_renderer"
        version: "2.12.5"
        minCompatible: "2.12.0"
        dependencies: []
        interface: NULL

    fun_game spec
        isRoot: true
        name: "fun_game"
        version: "1.2.3"
        minCompatible: "1.2.0"
        dependencies: ["gl_renderer 2.12.0"]
        interface: NULL

    gl_renderer=2.12.5;; \
    /fun_game=1.2.3;;gl_renderer=2.12.0

    gl_renderer 2.12.5 ─▴2.12.0─
    fun_game 1.2.3     ─╨───────


### An application containing two modules that both depend on a third module

    event_queue spec
        name: "event_queue"
        version: "3.12.9"
        minCompatible: "3.12.0"
        dependencies: []
        interface: NULL

    collision spec
        name: "collision"
        version: "2.4.4"
        minCompatible: "2.4.0"
        dependencies: ["event_queue 3.12.4"]
        interface: NULL

    udp_network spec
        name: "udp_network"
        version: "1.3.8"
        minCompatible: "1.3.0"
        dependencies: ["event_queue 3.12.1"]
        interface:
            name: "network"
            version: "1.14.7"
            minCompatible: "1.14.0"
            dependencies: []
            interface: NULL

    fun_game spec
        name: "fun_game"
        version: "1.2.3"
        minCompatible: "1.2.0"
        dependencies: ["collision 2.4.0", "network 1.3.0"]
        interface: NULL

    network*=1.14.7;; \
    /;; \
    /event_queue=3.12.9;; \
    /collision=2.4.4;;event_queue=3.12.4 \
    /udp_network=1.3.8;network*=1.14.7;event_queue=3.12.1 \
    /fun_game=1.2.3;;collision=2.4.0,network*=1.14.5

    network* 1.14.7    ─────────▴1.14.7────▴1.14.5─
                                │          ║       
    event_queue 3.12.9 ─▴3.12.4─│─▴3.12.1──║───────
    collision 2.4.4    ─╨───────│─║─▴2.4.0─║───────
    udp_network 1.3.8  ─────────┴─╨─║──────║───────
    fun_game 1.2.3     ─────────────╨──────╨───────


### An application containing a module that extends another module

    gl_renderer spec
        name: "gl_renderer"
        version: "2.12.5"
        minCompatible: "2.12.0"
        dependencies: []
        interface: NULL

    advanced_renderer spec
        name: "advanced_renderer"
        version: "0.11.2"
        minCompatible: "0.11.0"
        dependencies: ["gl_renderer 2.12.0"]
        interface: NULL

    fun_game spec
        name: "fun_game"
        version: "1.2.3"
        minCompatible: "1.2.0"
        dependencies: ["advanced_renderer 0.11.0"]
        interface: NULL

    gl_renderer=2.12.5;; \
    /advanced_renderer=0.11.2;;gl_renderer=2.12.0 \
    /fun_game=1.2.3;;advanced_renderer=0.11.0

    gl_renderer 2.12.5       ─▴2.12.0───
    advanced_renderer 0.11.2 ─╨─▴0.11.0─
    fun_game 1.2.3           ───╨───────
