#include <godot_cpp/core/class_db.hpp>

#include "ClipsStringBuilder.h"

void godot::ClipsStringBuilder::_bind_methods() {
    ClassDB::bind_method(D_METHOD("sb_get_contents"), &ClipsStringBuilder::sb_get_contents);
    ClassDB::bind_method(D_METHOD("sb_append", "p_value"), &ClipsStringBuilder::sb_append);
    ClassDB::bind_method(D_METHOD("sb_append_int", "p_value"), &ClipsStringBuilder::sb_append_int);
    ClassDB::bind_method(D_METHOD("sb_append_float", "p_value"), &ClipsStringBuilder::sb_append_float);
    ClassDB::bind_method(D_METHOD("sb_reset"), &ClipsStringBuilder::sb_reset);
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

godot::String godot::ClipsStringBuilder::sb_get_contents() const {
    const char *contents;
    if (sb == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsStringBuilder.sb_get_contents] sb is null");
        contents = "";
    } else {
        contents = sb->contents;
    }

    godot::String result = String::utf8(contents);
    return result;
}

void godot::ClipsStringBuilder::sb_append(const godot::String &p_value) {
    const char *cstr = p_value.utf8().get_data();
    if (sb == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsStringBuilder.sb_add_char] sb is null");
        return;
    }
    SBAppend(sb, cstr);
}

void godot::ClipsStringBuilder::sb_append_int(const int64_t p_value) {
    sb_append(itos(p_value));
}

void godot::ClipsStringBuilder::sb_append_float(const double p_value) {
    sb_append(rtos(p_value));
}

void godot::ClipsStringBuilder::sb_reset() {
    if (sb == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsStringBuilder.sb_reset] sb is null");
        return;
    }
    SBReset(sb);
}
