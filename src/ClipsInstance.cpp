#include "ClipsInstance.h"

void godot::ClipsInstance::_bind_methods() {
}

void godot::ClipsInstance::set_instance(Instance *p_instance) {
    RetainInstance(p_instance);
    instance = p_instance;
}

godot::ClipsInstance::~ClipsInstance() {
    ReleaseInstance(instance);
}
