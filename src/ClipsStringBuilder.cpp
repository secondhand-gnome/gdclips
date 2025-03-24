#include <godot_cpp/core/class_db.hpp>

#include "ClipsStringBuilder.h"

void godot::ClipsStringBuilder::_bind_methods() {
}

godot::ClipsStringBuilder::~ClipsStringBuilder() {
    if (sb == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsStringBuilder.destructor] sb is null");
        return;
    }
    SBDispose(sb);
}

void godot::ClipsStringBuilder::set_sb(StringBuilder *p_sb) {
    sb = p_sb;
}
