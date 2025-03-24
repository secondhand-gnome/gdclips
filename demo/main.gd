extends Node2D

func _ready() -> void:
	var clips_env := $ClipsEnv
	var cv := clips_env.clips_eval("80") as ClipsValue
	
	#var fact = clips_env.clips_assert_string("(fruit apple")
	
	var fcb = clips_env.clips_create_function_call_builder(1) as ClipsFunctionCallBuilder
	fcb.fcb_reset()
	fcb.fcb_append(cv)
	fcb.fcb_call("println", cv) # TODO no function has name "println"
	
	var sb = clips_env.clips_create_string_builder(1) as ClipsStringBuilder
	
	sb.sb_append("AA")
	sb.sb_append("B")
	sb.sb_append("C")
	print(sb.sb_get_contents()) # prints "BC"
	
	sb.sb_reset()
	print(sb.sb_get_contents()) # prints ""
