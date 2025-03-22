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
    ClassDB::bind_method(D_METHOD("clear_environment"), &GDClips::clear_environment);
    ClassDB::bind_method(D_METHOD("load_clips_file", "p_file_name"), &GDClips::load_clips_file);
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

bool GDClips::clear_environment() {
    return Clear(env);
}

bool GDClips::load_clips_file(const godot::String &p_file_name) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    const LoadError err = Load(env, file_name_cstr);
    switch (err) {
        case LE_NO_ERROR:
            return true;
        case LE_OPEN_FILE_ERROR:
            godot::UtilityFunctions::print("Error loading clips file: ", file_name_cstr);
            return false;
        case LE_PARSING_ERROR:
            godot::UtilityFunctions::print("Error parsing clips file: ", file_name_cstr);
            return false;
    }
}
