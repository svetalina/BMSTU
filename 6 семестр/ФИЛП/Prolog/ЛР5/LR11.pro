DOMAINS 

	list = integer*

PREDICATES
	
	len(list, integer).
	len_rec(list, integer, integer).
	
	sum(list, integer).
	sum_rec(list, integer, integer).
	
	sum_odd_pos(list, integer).
	sum_odd_pos_rec(list, integer, integer).
	
	
	el_larger(list, integer, list).
	el_larger_rec(list, integer, list, list).
	
	rm_el(list, integer, list).
	rm_el_rec(list, integer, list, list).
	
	merge(list, list, list).
	merge_rec(list, list, list, list).
	
	append(list, list, list).

CLAUSES
	
	%1
	len_rec([], Res, Res) :- !.

	len_rec([_|T], Res, Cur) :-
		Cur_res = Cur + 1,
		len_rec(T, Res, Cur_res).
		
	len(List, Res) :- 
		len_rec(List, Res, 0).
	
	% 2
	sum_rec([], Res, Res) :- !.

	sum_rec([H|T], Res, Cur) :-
		Cur_res = Cur + H,
		sum_rec(T, Res, Cur_res).
		
	sum(List, Res) :- 
		sum_rec(List, Res, 0).
	
	%3	
	sum_odd_pos_rec([], Res, Res) :- !.

	sum_odd_pos_rec([_|[H|T]], Res, Cur) :-
		Cur_res = Cur + H,
		sum_odd_pos_rec(T, Res, Cur_res), !.

	sum_odd_pos_rec([_|[H|_]], Res, Cur) :- 
		Res = Cur + H.
		
	sum_odd_pos(List, Res) :- 
		sum_odd_pos_rec(List, Res, 0).
	
	%4
	el_larger_rec([], _, Res, Res) :- !.
	
	el_larger_rec([H|T], Num, Res, Cur_res) :-
		H > Num, !, 
		el_larger_rec(T, Num, Res, [H|Cur_res]).

	el_larger_rec([_|T], Num, Res, Cur_res) :- 
		el_larger_rec(T, Num, Res, Cur_res).	
		
	el_larger(List, Num, Res) :- el_larger_rec(List, Num, Res, []).
	
	%5
	rm_el_rec([], _, Res, Res) :- !.
	
	rm_el_rec([H|T], Num, Res, Cur_res) :-
		H <> Num, !,
		rm_el_rec(T, Num, Res, [H|Cur_res]).

	rm_el_rec([_|T], Num, Res, Cur_res) :-
		rm_el_rec(T, Num, Res, Cur_res).

	rm_el(List, Num, Res) :- rm_el_rec(List, Num, Res, []).
	
	%6.1
	merge_rec([], [], Res, Res) :- !.
	merge_rec([H|T1], List2, Res, Cur_res) :- 
		!, merge_rec(T1, List2, Res, [H|Cur_res]).
	merge_rec(List1, [H|T2], Res, Cur_res) :- 
		!, merge_rec(List1, T2, Res, [H|Cur_res]).
	
	merge(List1, List2, Res) :- merge_rec(List1, List2, Res, []).
	
	%6.2
	append ([], L2, L2).
	append ([H|T1], L2, [H|T3]) :- append (T1, L2, T3).
		
GOAL
	%len([1, 2, 3, 4], Res). 
	%sum([1, 2, 3, 4], Res). 
	%sum_odd_pos([1, 2, 3, 4, 5], Res). 
	
	%el_larger([1, 2, 3, 4], 2, Res).
	%rm_el([3, 1, 3, 2, 3], 1, Res).
	merge([1, 2, 3], [4, 5], Res).