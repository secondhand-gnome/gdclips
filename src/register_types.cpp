#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "ClipsFact.h"
#include "gdclips.h"

using namespace godot;

void initialize_clips_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    GDREGISTER_RUNTIME_CLASS(GDClips);
    GDREGISTER_RUNTIME_CLASS(ClipsFact);
}

void uninitialize_clips_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT gdclips_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
                                        const GDExtensionClassLibraryPtr p_library,
                                        GDExtensionInitialization *r_initialization) {
    GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_clips_module);
    init_obj.register_terminator(uninitialize_clips_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}
