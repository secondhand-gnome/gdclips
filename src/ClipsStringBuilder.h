#ifndef CLIPSSTRINGBUILDER_H
#define CLIPSSTRINGBUILDER_H

#include <godot_cpp/classes/ref_counted.hpp>

extern "C" {
#include <clips.h>
}

namespace godot {
    class ClipsStringBuilder : public RefCounted {
        GDCLASS(ClipsStringBuilder, RefCounted)

    private:
        /// Pointer to a StringBuilder in memory managed by CLIPS
        StringBuilder *sb = nullptr;

    protected:
        static void _bind_methods();

    public:
        ~ClipsStringBuilder() override;

        void set_sb(StringBuilder *p_sb);

        godot::String sb_get_contents() const;

        /// 4.4.2 SBAddChar - Not implemented because Godot has no char type.
        /// Just use sb_append.

        /// 4.4.3 SBAppend
        void sb_append(const godot::String &p_value);

        /// 4.4.3 SBAppendInteger
        void sb_append_int(int64_t p_value);

        /// 4.4.3 SBAppendFloat
        void sb_append_float(double p_value);

        /// 4.4.4 SBCopy - Not implemented.
        /// Just use sb_get_contents()

        /// 4.4.6 SBReset
        void sb_reset();
    };
}


#endif //CLIPSSTRINGBUILDER_H
