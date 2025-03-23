#ifndef CLIPSFACT_H
#define CLIPSFACT_H


#include <godot_cpp/classes/ref_counted.hpp>

extern "C" {
#include "clips.h"
}

namespace godot {
    class ClipsFact : public RefCounted {
        GDCLASS(ClipsFact, RefCounted)

    private:
        Fact *fact;

    protected:
        static void _bind_methods();

    public:
        /// Must be called after ClipsFact is created with Ref.instantiate()
        void set_fact(Fact *p_fact);

        /// 3.3.3 Retract
        ~ClipsFact() override;
    };
}


#endif //CLIPSFACT_H
