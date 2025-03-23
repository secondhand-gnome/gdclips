#ifndef CLIPSINSTANCE_H
#define CLIPSINSTANCE_H


#include <godot_cpp/classes/ref_counted.hpp>

extern "C" {
#include "clips.h"
}

namespace godot {
    class ClipsInstance : public RefCounted {
        GDCLASS(ClipsInstance, RefCounted)

    private:
        Instance *instance;

    protected:
        static void _bind_methods();

    public:
        /// Must be called after ClipsInstance is created with Ref.instantiate()
        void set_instance(Instance *p_instance);

        ~ClipsInstance() override;
    };
}


#endif //CLIPSINSTANCE_H
