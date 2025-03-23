#include "ClipsValue.h"

void godot::ClipsValue::_bind_methods() {
}

void godot::ClipsValue::set_cv(CLIPSValue *p_cv) {
    cv = p_cv;
}

CLIPSValue *godot::ClipsValue::get_cv() const {
    return cv;
}
