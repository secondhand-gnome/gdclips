#ifndef GDCLIPS_H
#define GDCLIPS_H

#include <envrnmnt.h>
#include <godot_cpp/classes/node.hpp>

namespace godot {
    class GDClips : public Node {
        GDCLASS(GDClips, Node)

    private:
        double xxx;

    private:
        Environment *env;

    protected:
        static void _bind_methods();

    public:
        GDClips();

        ~GDClips() override;

        void _process(double delta) override;
    };
}

#endif //GDCLIPS_H
