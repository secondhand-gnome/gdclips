#ifndef GDCLIPS_H
#define GDCLIPS_H

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {
    class GDClips : public Sprite2D {
        GDCLASS(GDClips, Sprite2D)

    private:
        double xxx;

    protected:
        static void _bind_methods();

    public:
        GDClips();
        ~GDClips();

        void _process(double delta) override;
    };
}

#endif //GDCLIPS_H
