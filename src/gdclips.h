#ifndef GDCLIPS_H
#define GDCLIPS_H

#include <godot_cpp/classes/node.hpp>

extern "C" {
#include <clips.h>
}

namespace godot {
    class GDClips : public Node {
        GDCLASS(GDClips, Node)

    private:
        Environment *env;

    protected:
        static void _bind_methods();

    public:
        GDClips();

        ~GDClips() override;

        void _process(double delta) override;

        void _ready() override;

        bool clear_environment();
    };
}

#endif //GDCLIPS_H
