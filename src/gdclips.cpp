#include "gdclips.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <clips.h>

using namespace godot;

GDClips::GDClips() {
    env = CreateEnvironment();
}

GDClips::~GDClips() {
    DestroyEnvironment(env);
}

void GDClips::_bind_methods() {
}

void GDClips::_process(double delta) {
    godot::UtilityFunctions::print("clips!");
}
