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
        /// Pointer to a Fact in memory managed by CLIPS
        Fact *fact = nullptr;

    protected:
        static void _bind_methods();

    public:
        Fact *get_fact();
        void set_fact(Fact *p_fact);

        /// 3.3.3 Retract
        ~ClipsFact() override;
    };
}


#endif //CLIPSFACT_H
