extends Node2D

func _ready() -> void:
	var clips_env := $ClipsEnv
	var cv := clips_env.clips_eval("80") as ClipsValue
	
	var fact = clips_env.clips_assert_string("(fruit apple")
