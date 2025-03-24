#include <godot_cpp/core/class_db.hpp>

#include "ClipsInstance.h"

void godot::ClipsInstance::_bind_methods() {
}

Instance *godot::ClipsInstance::get_instance() const {
    return instance;
}

void godot::ClipsInstance::set_instance(Instance *p_instance) {
    RetainInstance(p_instance);
    instance = p_instance;
}

godot::ClipsInstance::~ClipsInstance() {
    ReleaseInstance(instance);

    UnmakeInstanceError err = UnmakeInstance(instance);
    switch (err) {
        case UIE_NO_ERROR:
            // No error
            break;
        case UIE_NULL_POINTER_ERROR:
            godot::UtilityFunctions::push_error("[ClipsInstance.destructor] The i parameter was NULL.");
            break;
        case UIE_COULD_NOT_DELETE_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsInstance.destructor] The instance could not be deleted (such as when pattern matching of a fact or instance is already occurring).");
            break;
        case UIE_DELETED_ERROR:
            godot::UtilityFunctions::push_error("[ClipsInstance.destructor] THe instance was already deleted.");
            break;
        case UIE_RULE_NETWORK_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsInstance.destructor] An error occured while the deletion was being processed in the rule network.");
            break;
    }
}
