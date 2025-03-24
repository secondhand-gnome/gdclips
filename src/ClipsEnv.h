#ifndef CLIPSENV_H
#define CLIPSENV_H

#include <godot_cpp/classes/node.hpp>

namespace godot {
    class ClipsFunctionCallBuilder;
}

extern "C" {
#include <clips.h>
}

namespace godot {
    class ClipsFact;
    class ClipsInstance;
    class ClipsValue;

    class ClipsEnv : public Node {
        GDCLASS(ClipsEnv, Node)

    private:
        Environment *env;

    protected:
        static void _bind_methods();

    public:
        ClipsEnv();

        ~ClipsEnv() override;

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

        /// 3.3.2 MakeInstance
        Ref<ClipsInstance> clips_make_instance(const godot::String &p_str);

        /// 3.3.5 LoadFacts
        long clips_load_facts(const godot::String &p_file_name);

        /// 3.3.5 BinaryLoadFacts
        long clips_binary_load_facts(const godot::String &p_file_name);

        /// 3.3.5 LoadFactsFromString
        long clips_load_facts_from_string(const godot::String &p_str);

        /// 3.3.6 SaveFacts
        long clips_save_facts(const godot::String &p_file_name, bool p_local_only);

        /// 3.3.6 BinarySaveFacts
        long clips_binary_save_facts(const godot::String &p_file_name, bool p_local_only);

        /// 3.3.7 LoadInstances
        long clips_load_instances(const godot::String &p_file_name);

        /// 3.3.7 BinaryLoadInstances
        long clips_binary_load_instances(const godot::String &p_file_name);

        /// 3.3.7 LoadInstancesFromString
        long clips_load_instances_from_string(const godot::String &p_str);

        /// 3.3.8 RestoreInstances
        long clips_restore_instances(const godot::String &p_file_name);

        /// 3.3.8 RestoreInstancesFromString
        long clips_restore_instances_from_string(const godot::String &p_str);

        /// 3.3.9 SaveInstances
        long clips_save_instances(const godot::String &p_file_name, bool p_local_only);

        /// 3.3.9 BinarySaveInstances
        long clips_binary_save_instances(const godot::String &p_file_name, bool p_local_only);

        /// 3.4 Executing Rules

        /// 3.4.1 Reset
        void clips_reset();

        /// 3.4.2 Run
        int64_t clips_run(int64_t p_limit);

        /// 3.5 Debugging

        /// 3.5.1 DribbleOn
        bool clips_dribble_on(const godot::String &p_file_name);

        /// 3.5.1 DribbleOff
        bool clips_dribble_off();

        /// 3.5.2 Watch
        // TODO methods for every type of WatchItem
        void clips_watch_all();

        /// 3.5.2 Unwatch
        // TODO methods for every type of WatchItem
        void clips_unwatch_all();

        /// 4.2 Eval
        godot::Ref<godot::ClipsValue> clips_eval(const godot::String &p_str);

        /// 4.2 Build
        bool clips_build(const godot::String &p_str);

        /// 4.3 FunctionCallBuilder
        godot::Ref<godot::ClipsFunctionCallBuilder> clips_create_function_call_builder(size_t p_capacity);

        /// TODO 4.4 StringBuilder Functions
    };
}

#endif //CLIPSENV_H
