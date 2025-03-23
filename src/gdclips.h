#ifndef GDCLIPS_H
#define GDCLIPS_H

#include <godot_cpp/classes/node.hpp>

extern "C" {
#include <clips.h>
}

namespace godot {
    class ClipsFact;

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

        /// Secton 3: Core Functions

        /// 3.2 Loading constructs

        /// 3.2.1 Clear
        bool clips_clear();

        /// 3.2.2 Load
        bool clips_load(const godot::String &p_file_name);

        /// 3.2.3 Bload
        bool clips_bload(const godot::String &p_file_name);

        /// 3.3 Creating and Removing Facts and Instances

        /// 3.3.1 AssertString
        Ref<ClipsFact> clips_assert_string(const godot::String &p_str);
    };
}

#endif //GDCLIPS_H
