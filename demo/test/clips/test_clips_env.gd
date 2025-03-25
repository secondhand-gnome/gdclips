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

# TODO 4.5.3 Multifield Iteration

# 4.5.4 Fact Query
func test_fact_query():
	var create_numbers = func(sb: ClipsStringBuilder, how_many: int) -> void:
		sb.sb_append("(list (numbers")
		for i in range(0, how_many):
			# Generate a random number in range 0-99
			var cv: ClipsValue = env.clips_eval("(sym-cat (random 0 99))")
			sb.sb_append(" ")

			# TODO
			# var lex := cv as ClipsLexemeValue
			# sb.sb_append(lex.contents)
			sb.sb_append("12") # TODO remove

		sb.sb_append("))")

		env.clips_watch_all() # TODO watch facts
		var fact: ClipsFact = env.clips_assert_string(sb.sb_get_contents())
		print(fact)
		env.clips_unwatch_all() # TODO unwatch facts

		sb.sb_reset()

	var print_numbers = func() -> void:
		# TODO - requires Write and WriteCLIPSValue
		pass

	# TODO main
	var sb: ClipsStringBuilder = env.clips_create_string_builder(512)
	create_numbers.call(sb, 10)

# 4.5.5 Function Call Builder
func test_function_call_builder():
	env.clips_build("(defclass POINT (is-a USER) (slot x) (slot y))")
	var ins: ClipsInstance = env.clips_make_instance("([p1] of POINT (x 3) (y 4))")
	var fcb: ClipsFunctionCallBuilder = env.clips_create_function_call_builder(2)
	fcb.fcb_append_instance(ins)
	fcb.fcb_append_symbol("print")
	assert_true(fcb.fcb_call("send", null))

	# TODO assert that the print output was:
	# [p1] of POINT
	# (x 3)
	# (y 4)
