//
// Created by austin on 3/22/25.
//

#include <godot_cpp/core/class_db.hpp>

#include "ClipsFact.h"

void godot::ClipsFact::_bind_methods() {
}

void godot::ClipsFact::set_fact(Fact *p_fact) {
    fact = p_fact;
    RetainFact(fact);
}

godot::ClipsFact::~ClipsFact() {
    ReleaseFact(fact);
    Retract(fact);
}
