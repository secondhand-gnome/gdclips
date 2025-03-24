#include <godot_cpp/core/class_db.hpp>

#include "ClipsStringBuilder.h"

void godot::ClipsStringBuilder::_bind_methods() {
    ClassDB::bind_method(D_METHOD("sb_add_char", "p_char"), &ClipsStringBuilder::sb_add_char);
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

void godot::ClipsStringBuilder::sb_add_char(const godot::String &p_char) {
    if (sb == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsStringBuilder.sb_add_char] sb is null");
        return;
    }
    if (p_char.length() != 1) {
        godot::UtilityFunctions::push_warning("[ClipsStringBuilder.sb_add_char] Expected one char, got ",
                                              p_char.length(), ": ", p_char);
        return;
    }
    const char c = p_char.unicode_at(0);
    SBAddChar(sb, c);
}
