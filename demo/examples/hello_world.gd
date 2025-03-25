extends Node2D

# 3.6.1 Hello World
func _ready() -> void:
	var env := $ClipsEnv
	env.clips_load("clp/hello.clp")
	env.clips_reset()
	env.clips_run(-1)
