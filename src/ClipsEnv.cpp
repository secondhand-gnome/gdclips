#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "ClipsEnv.h"

#include <ClipsStringBuilder.h>

#include "ClipsFact.h"
#include "ClipsFunctionCallBuilder.h"
#include "ClipsInstance.h"
#include "ClipsValue.h"

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
    ClassDB::bind_method(D_METHOD("clips_load_instances", "p_file_name"), &ClipsEnv::clips_load_instances);
    ClassDB::bind_method(D_METHOD("clips_binary_load_instances", "p_file_name"),
                         &ClipsEnv::clips_binary_load_instances);
    ClassDB::bind_method(D_METHOD("clips_load_instances_from_string", "p_str"),
                         &ClipsEnv::clips_load_instances_from_string);
    ClassDB::bind_method(D_METHOD("clips_restore_instances", "p_file_name"), &ClipsEnv::clips_restore_instances);
    ClassDB::bind_method(D_METHOD("clips_restore_instances_from_string", "p_str"),
                         &ClipsEnv::clips_restore_instances_from_string);
    ClassDB::bind_method(D_METHOD("clips_save_instances", "p_file_name", "p_local_only"),
                         &ClipsEnv::clips_save_instances);
    ClassDB::bind_method(D_METHOD("clips_binary_save_instances", "p_file_name", "p_local_only"),
                         &ClipsEnv::clips_binary_save_instances);
    ClassDB::bind_method(D_METHOD("clips_reset"), &ClipsEnv::clips_reset);
    ClassDB::bind_method(D_METHOD("clips_run"), &ClipsEnv::clips_run);
    ClassDB::bind_method(D_METHOD("clips_dribble_on", "p_file_name"), &ClipsEnv::clips_dribble_on);
    ClassDB::bind_method(D_METHOD("clips_dribble_off"), &ClipsEnv::clips_dribble_off);

    ClassDB::bind_method(D_METHOD("clips_watch_all"), &ClipsEnv::clips_watch_all);
    ClassDB::bind_method(D_METHOD("clips_unwatch_all"), &ClipsEnv::clips_unwatch_all);

    ClassDB::bind_method(D_METHOD("clips_eval", "p_str"), &ClipsEnv::clips_eval);
    ClassDB::bind_method(D_METHOD("clips_build", "p_str"), &ClipsEnv::clips_build);

    ClassDB::bind_method(D_METHOD("clips_create_function_call_builder", "p_capacity"),
                         &ClipsEnv::clips_create_function_call_builder);
    ClassDB::bind_method(D_METHOD("clips_create_string_builder", "p_capacity"), &ClipsEnv::clips_create_string_builder);
}

void ClipsEnv::_process(double delta) {
    // godot::UtilityFunctions::print("clips!");
}

void ClipsEnv::_ready() {
    Node::_ready();
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

    godot::Ref<godot::ClipsFact> clips_fact = memnew(godot::ClipsFact);
    switch (err) {
        case ASE_NO_ERROR:
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

int64_t ClipsEnv::clips_load_facts(const godot::String &p_file_name) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    return LoadFacts(env, file_name_cstr);
}

int64_t ClipsEnv::clips_binary_load_facts(const godot::String &p_file_name) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    return BinaryLoadFacts(env, file_name_cstr);
}

int64_t ClipsEnv::clips_load_facts_from_string(const godot::String &p_str) {
    const char *cstr = p_str.utf8().get_data();
    const size_t len = p_str.length();
    return LoadFactsFromString(env, cstr, len);
}

int64_t ClipsEnv::clips_save_facts(const godot::String &p_file_name, bool p_local_only) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    const SaveScope save_scope = p_local_only ? LOCAL_SAVE : VISIBLE_SAVE;
    return SaveFacts(env, file_name_cstr, save_scope);
}

int64_t ClipsEnv::clips_binary_save_facts(const godot::String &p_file_name, bool p_local_only) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    const SaveScope save_scope = p_local_only ? LOCAL_SAVE : VISIBLE_SAVE;
    return BinarySaveFacts(env, file_name_cstr, save_scope);
}

int64_t ClipsEnv::clips_load_instances(const godot::String &p_file_name) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    return LoadInstances(env, file_name_cstr);
}

int64_t ClipsEnv::clips_binary_load_instances(const godot::String &p_file_name) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    return BinaryLoadInstances(env, file_name_cstr);
}

int64_t ClipsEnv::clips_load_instances_from_string(const godot::String &p_str) {
    const char *cstr = p_str.utf8().get_data();
    const size_t len = p_str.length();
    return LoadInstancesFromString(env, cstr, len);
}

int64_t ClipsEnv::clips_restore_instances(const godot::String &p_file_name) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    return RestoreInstances(env, file_name_cstr);
}

int64_t ClipsEnv::clips_restore_instances_from_string(const godot::String &p_str) {
    const char *cstr = p_str.utf8().get_data();
    const size_t len = p_str.length();
    return RestoreInstancesFromString(env, cstr, len);
}

int64_t ClipsEnv::clips_save_instances(const godot::String &p_file_name, bool p_local_only) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    const SaveScope save_scope = p_local_only ? LOCAL_SAVE : VISIBLE_SAVE;
    return SaveInstances(env, file_name_cstr, save_scope);
}

int64_t ClipsEnv::clips_binary_save_instances(const godot::String &p_file_name, bool p_local_only) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    const SaveScope save_scope = p_local_only ? LOCAL_SAVE : VISIBLE_SAVE;
    return BinarySaveInstances(env, file_name_cstr, save_scope);
}

void ClipsEnv::clips_reset() {
    Reset(env);
}

int64_t ClipsEnv::clips_run(int64_t p_limit) {
    return Run(env, p_limit);
}

bool ClipsEnv::clips_dribble_on(const godot::String &p_file_name) {
    const char *file_name_cstr = p_file_name.utf8().get_data();
    return DribbleOn(env, file_name_cstr);
}

bool ClipsEnv::clips_dribble_off() {
    return DribbleOff(env);
}

void ClipsEnv::clips_watch_all() {
    Watch(env, ALL);
}

void ClipsEnv::clips_unwatch_all() {
    Unwatch(env, ALL);
}

godot::Ref<godot::ClipsValue> ClipsEnv::clips_eval(const godot::String &p_str) {
    const char *cstr = p_str.utf8().get_data();

    godot::Ref<godot::ClipsValue> clips_value = memnew(godot::ClipsValue);

    CLIPSValue cv;
    const EvalError err = Eval(env, cstr, &cv);

    switch (err) {
        case EE_NO_ERROR:
            // Copy cv to the Ref to be returned
            clips_value->set_cv(cv);
            break;
        case EE_PARSING_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsEnv.clips_eval] A syntax error was encountered while parsing: ",
                p_str);
            break;
        case EE_PROCESSING_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsEnv.clips_eval] An error occurred while executing the parsed expression: ",
                p_str);
            break;
    }
    return clips_value;
}

bool ClipsEnv::clips_build(const godot::String &p_str) {
    const char *cstr = p_str.utf8().get_data();
    const BuildError err = Build(env, cstr);

    bool result;
    switch (err) {
        case BE_NO_ERROR:
            // No error
            result = true;
            break;
        case BE_PARSING_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsEnv.clips_build] A syntax error was encountered while parsing: ",
                p_str);
            result = false;
            break;
        case BE_CONSTRUCT_NOT_FOUND_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsEnv.clips_build] The construct name following the opening left parenthesis was not recognized: ",
                p_str);
            result = false;
            break;
        case BE_COULD_NOT_BUILD_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsEnv.clips_build] The construct could not be added (such as when pattern matching is active): ",
                p_str);
            result = false;
            break;
    }
    return result;
}

godot::Ref<godot::ClipsFunctionCallBuilder> ClipsEnv::clips_create_function_call_builder(const int64_t p_capacity) {
    godot::Ref<godot::ClipsFunctionCallBuilder> clips_function_call_builder = memnew(godot::ClipsFunctionCallBuilder);
    FunctionCallBuilder *fcb = CreateFunctionCallBuilder(env, p_capacity);
    clips_function_call_builder->set_fcb(fcb);
    return clips_function_call_builder;
}

godot::Ref<godot::ClipsStringBuilder> ClipsEnv::clips_create_string_builder(int64_t p_capacity) {
    godot::Ref<godot::ClipsStringBuilder> clips_string_builder = memnew(godot::ClipsStringBuilder);
    StringBuilder *sb = CreateStringBuilder(env, p_capacity);
    clips_string_builder->set_sb(sb);
    return clips_string_builder;
}
