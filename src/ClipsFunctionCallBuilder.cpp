#include "ClipsFunctionCallBuilder.h"

#include <ClipsValue.h>

void godot::ClipsFunctionCallBuilder::_bind_methods() {
    ClassDB::bind_method(D_METHOD("fcb_call", "p_function_name", "p_clips_value"), &ClipsFunctionCallBuilder::fcb_call);
    ClassDB::bind_method(D_METHOD("fcb_reset"), &ClipsFunctionCallBuilder::fcb_reset);
    ClassDB::bind_method(D_METHOD("fcb_append", "p_clips_value"), &ClipsFunctionCallBuilder::fcb_append);
}

godot::ClipsFunctionCallBuilder::~ClipsFunctionCallBuilder() {
    if (fcb == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsFunctionCallBuilder.destructor] fcb is null");
        return;
    }
    FCBDispose(fcb);
}

void godot::ClipsFunctionCallBuilder::set_fcb(FunctionCallBuilder *p_fcb) {
    fcb = p_fcb;
}

bool godot::ClipsFunctionCallBuilder::fcb_call(const godot::String &p_function_name,
                                               const godot::Ref<godot::ClipsValue>& p_clips_value) {
    const char *fn_cstr = p_function_name.utf8().get_data();

    if (fcb == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsFunctionCallBuilder.fcb_call] fcb is null");
        return false;
    }
    CLIPSValue *cv = p_clips_value->get_cv();
    if (cv == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsFunctionCallBuilder.fcb_call] cv is null");
        return false;
    }

    const FunctionCallBuilderError err = FCBCall(fcb, fn_cstr, cv);
    switch (err) {
        case FCBE_NO_ERROR:
            return true;
        case FCBE_NULL_POINTER_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsFunctionCallBuilder.fcb_call] The fcb or functionName parameter was NULL.");
            break;
        case FCBE_FUNCTION_NOT_FOUND_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsFunctionCallBuilder.fcb_call] A function, deffunction, or generic function could not be found with the name specified by the functionName parameter: ",
                p_function_name);
            break;
        case FCBE_INVALID_FUNCTION_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsFunctionCallBuilder.fcb_call] The function or command has a specialized parser (such as the assert command) and cannot be invoked.: ",
                p_function_name);
            break;
        case FCBE_ARGUMENT_COUNT_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsFunctionCallBuilder.fcb_call] The function was passed the incorrect number of arguments: ",
                p_function_name);
            break;
        case FCBE_ARGUMENT_TYPE_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsFunctionCallBuilder.fcb_call] The function was passed an argument with an invalid type: ",
                p_function_name);
            break;
        case FCBE_PROCESSING_ERROR:
            godot::UtilityFunctions::push_error(
                "[ClipsFunctionCallBuilder.fcb_call] An error occurred while the function was being evaluated: ",
                p_function_name);
            break;
    }
    return false;
}

void godot::ClipsFunctionCallBuilder::fcb_reset() {
    if (fcb == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsFunctionCallBuilder.clips_reset] fcb is null");
        return;
    }
    FCBReset(fcb);
}

void godot::ClipsFunctionCallBuilder::fcb_append(godot::Ref<godot::ClipsValue> p_clips_value) {
    if (fcb == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsFunctionCallBuilder.clips_append] fcb is null");
        return;
    }
    CLIPSValue *cv = p_clips_value->get_cv();
    if (cv == nullptr) {
        godot::UtilityFunctions::push_warning("[ClipsFunctionCallBuilder.clips_append] cv is null");
        return;
    }
    FCBAppend(fcb, cv);
}
