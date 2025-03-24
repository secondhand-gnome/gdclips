#ifndef CLIPSFUNCTIONCALLBUILDER_H
#define CLIPSFUNCTIONCALLBUILDER_H


#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {
    class ClipsValue;
}

extern "C" {
#include <clips.h>
}

namespace godot {
    class ClipsFunctionCallBuilder : public RefCounted {
        GDCLASS(ClipsFunctionCallBuilder, RefCounted)

    private:
        /// Pointer to a FunctionCallBuilder in memory managed by CLIPS
        FunctionCallBuilder *fcb = nullptr;

    protected:
        static void _bind_methods();

    public:
        ~ClipsFunctionCallBuilder() override;

        void set_fcb(FunctionCallBuilder *p_fcb);

        bool fcb_call(const godot::String &p_function_name, const godot::Ref<godot::ClipsValue> &p_clips_value);

        void fcb_reset();

        void fcb_append(const godot::Ref<godot::ClipsValue> &p_clips_value);

        // TODO FCBAppendUDFValue

        void fcb_append_integer(int64_t p_value);

        void fcb_append_float(double p_value);

        void fcb_append_symbol(const godot::String &p_value);

        void fcb_append_string(const godot::String &p_value);

        void fcb_append_instance_name(const godot::String &p_value);

        // TODO append CLIPSInteger
        // TODO append CLIPSFloat
        // TODO append CLIPSLexeme
        // TODO append Fact
        // TODO append Instance
        // TODO append Multifield
        // TODO append CLIPSExternalAddress
    };
}


#endif //CLIPSFUNCTIONCALLBUILDER_H
