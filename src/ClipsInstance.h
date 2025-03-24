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
        void set_instance(Instance *p_instance);

        /// 3.3.4 UnmakeInstance
        ~ClipsInstance() override;
    };
}


#endif //CLIPSINSTANCE_H
