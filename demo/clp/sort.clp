(deftemplate list
	(multislot numbers))

(defrule sort
	?f <- (list (numbers $?b ?x ?y&:(> ?x ?y) $?e))
	=>
	(modify ?f (numbers ?b ?y ?x ?e)))

