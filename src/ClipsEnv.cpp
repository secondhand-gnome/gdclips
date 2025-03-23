#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "ClipsFact.h"
#include "ClipsEnv.h"
#include "ClipsInstance.h"

using namespace godot;

ClipsEnv::ClipsEnv() {
    env = CreateEnvironment();
}

ClipsEnv::~ClipsEnv() {
    DestroyEnvironment(env);
}

void ClipsEnv::_bind_methods() {
    ClassDB::bind_method(D_METHOD("clips_clear"), &ClipsEnv::clips_clear);
    ClassDB::bind_method(D_METHOD("clips_load", "p_file_name"), &ClipsEnv::clips_load);
    ClassDB::bind_method(D_METHOD("clips_bload", "p_file_name"), &ClipsEnv::clips_bload);
    ClassDB::bind_method(D_METHOD("clips_assert_string", "p_str"), &ClipsEnv::clips_assert_string);
    ClassDB::bind_method(D_METHOD("clips_make_instance", "p_str"), &ClipsEnv::clips_make_instance);
    ClassDB::bind_method(D_METHOD("clips_load_facts", "p_file_name"), &ClipsEnv::clips_load_facts);
    ClassDB::bind_method(D_METHOD("clips_binary_load_facts", "p_file_name"), &ClipsEnv::clips_binary_load_facts);
    ClassDB::bind_method(D_METHOD("clips_load_facts_from_string", "p_str"), &ClipsEnv::clips_load_facts_from_string);
    ClassDB::bind_method(D_METHOD("clips_save_facts", "p_file_name", "p_local_only"), &ClipsEnv::clips_save_facts);
    ClassDB::bind_method(D_METHOD("clips_binary_save_facts", "p_file_name", "p_local_only"),
                         &ClipsEnv::clips_binary_save_facts);
}

void ClipsEnv::_process(double delta) {
    // godot::UtilityFunctions::print("clips!");
}

void ClipsEnv::_ready() {
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

    godot::UtilityFunctions::print("ClipsEnv ", get_name(), " ready");
}

bool ClipsEnv::clips_clear() {
    return Clear(env);
}

bool ClipsEnv::clips_load(const godot::String &p_file_name) {
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

bool ClipsEnv::clips_bload(const godot::String &p_file_name) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    return Bload(env, file_name_cstr);
}

Ref<ClipsFact> ClipsEnv::clips_assert_string(const godot::String &p_str) {
    const char *cstr = p_str.utf8().get_data();
    Fact *fact = AssertString(env, cstr);

    AssertStringError err = GetAssertStringError(env);

    Ref<ClipsFact> clips_fact;
    switch (err) {
        case ASE_NO_ERROR:
            clips_fact.instantiate();
            clips_fact->set_fact(fact);
            break;
        case ASE_NULL_POINTER_ERROR:
            godot::UtilityFunctions::push_error("[ClipsEnv.clips_assert_string] The str parameter was NULL.");
            break;
        case ASE_PARSING_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsEnv.clips_assert_string] An error was encountered parsing the str parameter: ",
                p_str);
            break;
        case ASE_COULD_NOT_ASSERT_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsEnv.clips_assert_string] The fact could not be asserted (such as when pattern matching of a fact or instance is already occurring): ",
                p_str);
            break;
        case ASE_RULE_NETWORK_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsEnv.clips_assert_string] An error occurred while the assertion was being processed in the rule network: ",
                p_str);
            break;
    }
    return clips_fact;
}

Ref<ClipsInstance> ClipsEnv::clips_make_instance(const godot::String &p_str) {
    const char *cstr = p_str.utf8().get_data();
    Instance *instance = MakeInstance(env, cstr);

    MakeInstanceError err = GetMakeInstanceError(env);

    Ref<ClipsInstance> clips_instance;
    switch (err) {
        case MIE_NO_ERROR:
            clips_instance.instantiate();
            clips_instance->set_instance(instance);
            break;
        case MIE_NULL_POINTER_ERROR:
            godot::UtilityFunctions::push_error("[ClipsEnv.clips_make_instance] The str parameter was NULL.");
            break;
        case MIE_PARSING_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsEnv.clips_make_instance] An error was encountered parsing the str parameter: ",
                p_str);
            break;
        case MIE_COULD_NOT_CREATE_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsEnv.clips_make_instance] The instance could not be created (such as when pattern matching of a fact or instance is already occurring): ",
                p_str);
            break;
        case MIE_RULE_NETWORK_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsEnv.clips_make_instance] An error occurred while the instance was being processed in the rule network: ",
                p_str);
            break;
    }
    return clips_instance;
}

long ClipsEnv::clips_load_facts(const godot::String &p_file_name) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    return LoadFacts(env, file_name_cstr);
}

long ClipsEnv::clips_binary_load_facts(const godot::String &p_file_name) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    return BinaryLoadFacts(env, file_name_cstr);
}

long ClipsEnv::clips_load_facts_from_string(const godot::String &p_str) {
    const char *cstr = p_str.utf8().get_data();
    const size_t len = p_str.length();
    return LoadFactsFromString(env, cstr, len);
}

long ClipsEnv::clips_save_facts(const godot::String &p_file_name, bool p_local_only) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    const SaveScope save_scope = p_local_only ? LOCAL_SAVE : VISIBLE_SAVE;
    return SaveFacts(env, file_name_cstr, save_scope);
}

long ClipsEnv::clips_binary_save_facts(const godot::String &p_file_name, bool p_local_only) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    const SaveScope save_scope = p_local_only ? LOCAL_SAVE : VISIBLE_SAVE;
    return BinarySaveFacts(env, file_name_cstr, save_scope);
}
