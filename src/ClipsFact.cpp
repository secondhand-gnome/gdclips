#include <godot_cpp/core/class_db.hpp>

#include "ClipsFact.h"

void godot::ClipsFact::_bind_methods() {
}

Fact * godot::ClipsFact::get_fact() {
    return fact;
}

void godot::ClipsFact::set_fact(Fact *p_fact) {
    fact = p_fact;
    RetainFact(fact);
}

godot::ClipsFact::~ClipsFact() {
    if (fact == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsFact.destructor] Fact is null.");
        return;
    }

    ReleaseFact(fact);

    RetractError err = Retract(fact);
    switch (err) {
        case RE_NO_ERROR:
            // No error
            break;
        case RE_NULL_POINTER_ERROR:
            godot::UtilityFunctions::push_error("[ClipsFact.destructor] The f parameter was NULL.");
            break;
        case RE_COULD_NOT_RETRACT_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsFact.destructor] The fact could not be retracted (such as when pattern matching of a fact or instance is already occurring)");
            break;
        case RE_RULE_NETWORK_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsFact.destructor] An error occurs while the retraction was being processed in the rule network.");
            break;
    }
}
