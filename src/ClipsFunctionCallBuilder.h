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

        bool fcb_call(const godot::String &p_function_name, const godot::Ref<godot::ClipsValue>& p_clips_value);

        void fcb_reset();

        void fcb_append(godot::Ref<godot::ClipsValue> p_clips_value);

        // TODO FCBAppendUDFValue
        // TODO THe rest of the FCBAppend methods
    };
}


#endif //CLIPSFUNCTIONCALLBUILDER_H
