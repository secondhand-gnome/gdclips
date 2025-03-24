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
    };
}


#endif //CLIPSSTRINGBUILDER_H
