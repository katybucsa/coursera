exception NoAnswer

datatype pattern = Wildcard
		 | Variable of string
		 | UnitP
		 | ConstP of int
		 | TupleP of pattern list
		 | ConstructorP of string * pattern

datatype valu = Const of int
	      | Unit
	      | Tuple of valu list
	      | Constructor of string * valu

fun g f1 f2 p =
    let 
	val r = g f1 f2 
    in
	case p of
	    Wildcard          => f1 ()
	  | Variable x        => f2 x
	  | TupleP ps         => List.foldl (fn (p,i) => (r p) + i) 0 ps
	  | ConstructorP(_,p) => r p
	  | _                 => 0
    end

(**** for the challenge problem only ****)

datatype typ = Anything
	     | UnitT
	     | IntT
	     | TupleT of typ list
	     | Datatype of string



(* 1. Write a function only_capitals that takes a string list and returns a string list that has only the strings in the argument that start with an uppercase letter. Assume all strings have at least 1 character. Use List.filter, Char.isUpper, and String.sub to make a 1-2 line solution. *)
 
fun only_capitals str_list = List.filter (fn str => Char.isUpper(String.sub(str, 0))) str_list


 
(* 2. Write a function longest_string1 that takes a string list and returns the longest string in the list. If the list is empty, return "". In the case of a tie, return the string closest to the beginning of the list. Use foldl, String.size, and no recursion (other than the implementation of foldl is recursive). *)

fun longest_string1 str_list = List.foldl (fn (s, acc) => if String.size(s) > String.size(acc) then s else acc) "" str_list



(* 3. Write a function longest_string2 that is exactly like longest_string1 except in the case of ties it returns the string closest to the end of the list. Your solution should be almost an exact copy of longest_string1. Still use foldl and String.size. *)
					  
fun longest_string2 str_list = List.foldl (fn (s, acc) => if String.size(s) >= String.size(acc) then s else acc) "" str_list



(* 4. Write functions longest_string_helper, longest_string3, and longest_string4 such that:
   • longest_string3 has the same behavior as longest_string1 and longest_string4 has the same behavior as longest_string2.
   • longest_string_helper has type (int * int -> bool) -> string list -> string (notice the currying). This function will look a lot like longest_string1 and longest_string2 but is more general because it takes a function as an argument.
   • If longest_string_helper is passed a function that behaves like > (so it returns true exactly when its first argument is stricly greater than its second), then the function returned has the same behavior as longest_string1.
   • longest_string3 and longest_string4 are defined with val-bindings and partial applications of longest_string_helper. *)					  

fun longest_string_helper f str_list = List.foldl (fn (s, acc) => if f (s, acc) then s else acc) "" str_list

val longest_string3 = longest_string_helper (fn (s1, s2) => String.size(s1) > String.size(s2))

val longest_string4 = longest_string_helper (fn (s1, s2) => String.size(s1) >= String.size(s2))



(* 5. Write a function longest_capitalized that takes a string list and returns the longest string in the list that begins with an uppercase letter, or "" if there are no such strings. Assume all strings have at least 1 character. Use a val-binding and the ML library’s o operator for composing functions. Resolve ties like in problem 2. *)

fun longest_capitalized str_list = (longest_string3 o only_capitals) str_list



(* 6. Write a function rev_string that takes a string and returns the string that is the same characters in reverse order. Use ML’s o operator, the library function rev for reversing lists, and two library functions in the String module. (Browse the module documentation to find the most useful functions.) *)

fun rev_string str = (String.implode o List.rev o String.explode) str



(* 7. Write a function first_answer of type (’a -> ’b option) -> ’a list -> ’b (notice the 2 arguments are curried). The first argument should be applied to elements of the second argument in order until the first time it returns SOME v for some v and then v is the result of the call to first_answer. If the first argument returns NONE for all list elements, then first_answer should raise the exception NoAnswer. Hints: Sample solution is 5 lines and does nothing fancy. *)

fun first_answer f elems =
    case elems of
	[] => raise NoAnswer
      | elem::elems' => case f elem of
			    NONE => first_answer f elems'
			  | SOME v => v



(* 8. Write a function all_answers of type (’a -> ’b list option) -> ’a list -> ’b list option (notice the 2 arguments are curried). The first argument should be applied to elements of the second argument. If it returns NONE for any element, then the result for all_answers is NONE. Else the calls to the first argument will have produced SOME lst1, SOME lst2, ... SOME lstn and the result of all_answers is SOME lst where lst is lst1, lst2, ..., lstn appended together (order doesn’t matter). Hints: The sample solution is 8 lines. It uses a helper function with an accumulator and uses @. Note all_answers f [] should evaluate to SOME []. *)

fun all_answers f elems =
    let
	fun local_helper_f [] [] = NONE
	  | local_helper_f acc [] = SOME acc
	  | local_helper_f acc (elem::elems') = case f elem of
					      NONE => local_helper_f acc elems'
					    | SOME l => local_helper_f (acc @ l) elems' 
    in
	local_helper_f [] elems
    end
	
			    

(* Given valu v and pattern p, either p matches v or not. If it does, the match produces a list of string * valu pairs; order in the list does not matter. The rules for matching should be unsurprising:
   • Wildcard matches everything and produces the empty list of bindings.
   • Variable s matches any value v and produces the one-element list holding (s,v).
   • UnitP matches only Unit and produces the empty list of bindings.
   • ConstP 17 matches only Const 17 and produces the empty list of bindings (and similarly for other integers).
   • TupleP ps matches a value of the form Tuple vs if ps and vs have the same length and for all i, the i th element of ps matches the i th element of vs. The list of bindings produced is all the lists from the nested pattern matches appended together.
   • ConstructorP(s1,p) matches Constructor(s2,v) if s1 and s2 are the same string (you can compare them with =) and p matches v. The list of bindings produced is the list from the nested pattern match. We call the strings s1 and s2 the constructor name.
   • Nothing else matches.  *)


(* 9. (This problem uses the pattern datatype but is not really about pattern-matching.) A function g has been provided to you. *)

(* (a) Use g to define a function count_wildcards that takes a pattern and returns how many Wildcard patterns it contains. *)

val count_wildcards = g (fn _ => 1) (fn _ => 0)

(* (b) Use g to define a function count_wild_and_variable_lengths that takes a pattern and returns the number of Wildcard patterns it contains plus the sum of the string lengths of all the variables in the variable patterns it contains. (Use String.size. We care only about variable names; the constructor names are not relevant.) *)


val count_wild_and_variable_lengths = g (fn _ => 1) (fn s => String.size(s))

(* (c) Use g to define a function count_some_var that takes a string and a pattern (as a pair) and returns the number of times the string appears as a variable in the pattern. We care only about variable names; the constructor names are not relevant. *)

fun count_some_var (str, p) = g (fn _ => 0) (fn s => if s = str then 1 else 0) p				




(* 10. Write a function check_pat that takes a pattern and returns true if and only if all the variables appearing in the pattern are distinct from each other (i.e., use different strings). The constructor names are not relevant. Hints: The sample solution uses two helper functions. The first takes a pattern and returns a list of all the strings it uses for variables. Using foldl with a function that uses @ is useful in one case. The second takes a list of strings and decides if it has repeats. List.exists may be useful. Sample solution is 15 lines. These are hints: We are not requiring foldl and List.exists here, but they make it easier. *)

fun check_pat pat =
    let
	fun get_all_strings acc pat =
	    case pat of
		Variable s => s::acc
	      | TupleP list_patterns => List.foldl (fn (p, acc) => get_all_strings acc p) acc list_patterns
	      | ConstructorP (s, pat') => get_all_strings (s::acc) pat'
	      | _ => acc

	fun check_uniq_elems str_list =
	    case str_list of
		[] => true
	      | s::str_list' => case List.exists (fn x => x = s) str_list' of
				    true => false
				  | _ => check_uniq_elems str_list'
    in
	check_uniq_elems (get_all_strings [] pat)
    end



(* 11. Write a function match that takes a valu * pattern and returns a (string * valu) list option, namely NONE if the pattern does not match and SOME lst where lst is the list of bindings if it does. Note that if the value matches but the pattern has no patterns of the form Variable s, then the result is SOME []. Hints: Sample solution has one case expression with 7 branches. The branch for tuples uses all_answers and ListPair.zip. Sample solution is 13 lines. Remember to look above for the rules for what patterns match what values, and what bindings they produce. These are hints: We are not requiring all_answers and ListPair.zip here, but they make it easier. *)

fun match (valuu, pat) =
    case (valuu, pat) of
	((_, Wildcard) | (Unit, UnitP) | (Const _, ConstP _)) => SOME []
      | (_, Variable s) => SOME [(s, valuu)]
      | (Tuple vs, TupleP ps) => if List.length vs = List.length ps
				 then all_answers match (ListPair.zip(vs, ps))
				 else NONE
      | (Constructor (s1, v), ConstructorP (s2, p)) => if s1 = s2 then match (v, p) else NONE
      | _ => NONE
								 
