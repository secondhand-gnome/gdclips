#include "gdclips.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GDClips::_bind_methods() {

}

void GDClips::_process(double delta) {
    godot::UtilityFunctions::print("clips!");
}
