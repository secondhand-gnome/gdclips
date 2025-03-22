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
    ClassDB::bind_method(D_METHOD("clear_environment"), &GDClips::clips_clear);
    ClassDB::bind_method(D_METHOD("load_clips_file", "p_file_name"), &GDClips::clips_load);
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

bool GDClips::clips_clear() {
    return Clear(env);
}

bool GDClips::clips_load(const godot::String &p_file_name) {
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

bool GDClips::clips_bload(const godot::String &p_file_name) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    return Bload(env, file_name_cstr);
}

void GDClips::clips_assert_string(const godot::String &p_str) {
    const char *cstr = p_str.utf8().get_data();
    Fact *fact = AssertString(env, cstr);

    AssertStringError err = GetAssertStringError(env);

    // TODO return Fact or null here
    switch (err) {
        case ASE_NO_ERROR:
            // TODO No error occurred
            return;
        case ASE_NULL_POINTER_ERROR:
            godot::UtilityFunctions::push_error("[GDClips] The str parameter was NULL.");
            return;
        case ASE_PARSING_ERROR:
            godot::UtilityFunctions::push_error("[GDClips] An error was encountered parsing the str parameter: ",
                                                p_str);
            return;
        case ASE_COULD_NOT_ASSERT_ERROR:
            godot::UtilityFunctions::push_error(
                "[GDClips] The fact could not be asserted (such as when pattern matching of a fact or instance is already occurring): ",
                p_str);
            return;
        case ASE_RULE_NETWORK_ERROR:
            godot::UtilityFunctions::push_error(
                "[GDClips] An error occurred while the assertion was being processed in the rule network: ", p_str);
            return;
    }
}
