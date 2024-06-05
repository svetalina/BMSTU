DOMAINS
  	name = string.
  	sex  = string.

PREDICATES
  	parent(sex, name, name).
  	grandParent(sex, sex, name, name).

CLAUSES
  	parent("w", "Irina",     "Marina").
  	parent("m", "Dmitry",    "Marina").
  	parent("w", "Valentina", "Irina").
  	parent("m", "Nikolay",   "Irina").
  	parent("w", "Zoya",      "Dmitry").
  	parent("m", "Victor",    "Dmitry").

  	grandParent(Side, Sex, GrandParent, Child) :-
   		parent(Side, Parent, Child),
    		parent(Sex,  GrandParent, Parent).

GOAL
  
	%grandParent(_, "w", GrandParent, "Marina").
  	%grandParent(_, "m", GrandParent, "Marina").
  	%grandParent(_, _, GrandParent, "Marina").
  	%grandParent("w", "w", GrandParent, "Marina").
  	grandParent("w", _, GrandParent, "Marina").
