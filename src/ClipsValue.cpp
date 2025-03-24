#include "ClipsValue.h"

void godot::ClipsValue::_bind_methods() {
}

CLIPSValue *godot::ClipsValue::get_cv() {
    return &cv;
}

void godot::ClipsValue::set_cv(const CLIPSValue p_cv) {
    cv = p_cv;
}
