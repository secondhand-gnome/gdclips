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

# 4.5.1 Debugging Revisited
func test_debugging_revisited():
	assert_true(env.clips_build("
		(deftemplate list
			(multislot numbers))"))
			
	assert_true(env.clips_build("
		(defrule sort
			?f <- (list (numbers $?b ?x ?y&:(> ?x ?y) $?e))
			=>
			(modify ?f (numbers ?b ?y ?x ?e)))"))
	
	# TODO - some of these throw syntax errors but it's unclear why
	env.clips_eval("(watch facts)")
	env.clips_eval("(watch rules)")
	env.clips_eval("(watch activations)")
	env.clips_eval("(dribble-on sort.dbg)")
	env.clips_eval("(reset)")
	env.clips_eval("(assert (list (numbers 61 31 27 48)))")
	env.clips_eval("(run)")
	env.clips_eval("(dribble-off)")

# 4.5.2 String Builder Function Call
func test_string_builder_function_call():
	var sb: ClipsStringBuilder = env.clips_create_string_builder(512)
	
	sb.sb_append("John")
	sb.sb_append(" ")
	sb.sb_append("Doe")
	
	assert_eq(sb.sb_get_contents(), "John Doe")
	
	# TODO evaluate (upcase) function here, get CV returned from eval
