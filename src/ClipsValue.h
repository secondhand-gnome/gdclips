#ifndef CLIPSVALUE_H
#define CLIPSVALUE_H

#include <godot_cpp/classes/ref_counted.hpp>

extern "C" {
#include <clips.h>
}

namespace godot {
    class ClipsValue : public RefCounted {
        GDCLASS(ClipsValue, RefCounted)

    private:
        CLIPSValue cv;

    protected:
        static void _bind_methods();

    public:
        CLIPSValue *get_cv();

        void set_cv(CLIPSValue p_cv);
    };
}


#endif //CLIPSVALUE_H
