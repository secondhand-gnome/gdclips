extends GutTest

var env: ClipsEnv

func before_each():
	env = ClipsEnv.new()

func after_each():
	env.free()

# 3.6.1 Hello World
func test_hello_world():
	assert_true(env.clips_load("clp/hello.clp"))
	env.clips_reset()
	assert_eq(1, env.clips_run(-1))

# 3.6.2 Debugging
func test_debugging():
	assert_true(env.clips_load("clp/sort.clp"))
	
	# TODO watch_facts, watch_rules, watch_activations
	env.clips_watch_all()
	assert_true(env.clips_dribble_on("sort.dbg"))
	env.clips_reset()
	
	var fact: ClipsFact = env.clips_assert_string("(list (numbers 61 31 27 48))")
	assert_eq(env.clips_run(-1), 4)
	assert_true(env.clips_dribble_off())
