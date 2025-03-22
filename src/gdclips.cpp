#include "gdclips.h"
#include <godot_cpp/variant/utility_functions.hpp>

extern "C" {
#include <clips.h>
}

using namespace godot;

GDClips::GDClips() {
    env = CreateEnvironment();
}

GDClips::~GDClips() {
    DestroyEnvironment(env);
}

void GDClips::_bind_methods() {
}

void GDClips::_process(double delta) {
    // godot::UtilityFunctions::print("clips!");
}

void GDClips::_ready() {
    Node::_ready();

    CLIPSValue defmoduleList;
    GetDefmoduleList(env, &defmoduleList);

    Multifield *multifield = defmoduleList.multifieldValue;
    if (multifield == nullptr) {
        godot::UtilityFunctions::print("multifield is null");
    } else {
        godot::UtilityFunctions::print("multifield is not null");



        // TODO print multifield
        // TODO make debug methods for printing Multifield and general CLIPSValue
    }

    godot::UtilityFunctions::print("GDClips ", get_name(), " ready");
}
