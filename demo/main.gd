extends Node2D

func _ready() -> void:
	var clips_env := $ClipsEnv
	var cv := clips_env.clips_eval("80") as ClipsValue
	print(type_string(typeof(cv)))
