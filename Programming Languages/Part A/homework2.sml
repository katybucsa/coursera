(* 1. This problem involves using first-name substitutions to come up with alternate names. For example,
Fredrick William Smith could also be Fred William Smith or Freddie William Smith. Only part (d) is
specifically about this, but the other problems are helpful. *)

(* if you use this function to compare two strings (returns true if the same
   string), then you avoid several of the functions in problem 1 having
   polymorphic types that may be confusing *)
fun same_string (s1 : string, s2 : string) = (* string * string *)
    s1 = s2

	     
(* a) Write a function all_except_option, which takes a string and a string list. Return NONE 
if the string is not in the list, else return SOME lst where lst is identical to the argument 
list except the string is not in it. You may assume the string is in the list at most once. 
Use same_string, provided to you, to compare strings. Sample solution is around 8 lines. *)
fun all_except_option (s, xs) = (* string * string list  *)
    case xs of
	[] => NONE
      | x::xs' => case same_string(s, x) of
		      true => SOME(xs')
		    | false => case all_except_option(s, xs') of
				  NONE => NONE
				| SOME xs1 => SOME(x::xs1)

(* b) Write a function get_substitutions1, which takes a string list list (a list of list of strings, the
substitutions) and a string s and returns a string list. The result has all the strings that are in
some list in substitutions that also has s, but s itself should not be in the result. Example:
get_substitutions1([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]],
"Fred")
(* answer: ["Fredrick","Freddie","F"] *)
Assume each list in substitutions has no repeats. The result will have repeats if s and another string are
both in more than one list in substitutions. Example:
get_substitutions1([["Fred","Fredrick"],["Jeff","Jeffrey"],["Geoff","Jeff","Jeffrey"]],
"Jeff")
(* answer: ["Jeffrey","Geoff","Jeffrey"] *)
Use part (a) and ML’s list-append (@) but no other helper functions. Sample solution is around 6 lines.  *)
fun get_substitutions1 (strs, s) = (* string list list * string *)
    case strs of
	[] => []
      | h::t => case all_except_option(s, h) of
		    NONE => get_substitutions1(t, s)
		  | SOME res => res @ get_substitutions1(t,s) 
						  
(* c) Write a function get_substitutions2, which is like get_substitutions1 except it uses a tail-recursive local helper function. *)
fun get_substitutions2 (strs, s) = (* string list list * string => string list *)
    let fun f (strs, s, acc) =
	    case strs of
		[] => acc
	      | h::t => case all_except_option(s, h) of
			    NONE => f(t,s, acc)
			  | SOME res => f(t, s, acc @ res)
    in
	f(strs, s, [])
    end


(* d) Write a function similar_names, which takes a string list list of substitutions (as in parts (b) and
(c)) and a full name of type {first:string,middle:string,last:string} and returns a list of full
names (type {first:string,middle:string,last:string} list). The result is all the full names you
can produce by substituting for the first name (and only the first name) using substitutions and parts (b)
or (c). The answer should begin with the original name (then have 0 or more other names). Example:
similar_names([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]],
{first="Fred", middle="W", last="Smith"})
(* answer: [{first="Fred", last="Smith", middle="W"},
{first="Fredrick", last="Smith", middle="W"},
{first="Freddie", last="Smith", middle="W"},
{first="F", last="Smith", middle="W"}] *)
Do not eliminate duplicates from the answer. Hint: Use a local helper function. Sample solution is
around 10 lines. *)
fun similar_names (strs, r as {first = f, middle = m, last = l}) =
    let fun helper_f (strs, r as {first = f, middle = m, last = l}, acc) =
	    case strs of
		[] => acc
	      | h::t => helper_f(t, r, acc @ [{first=h, middle = m, last = l}])
    in
	helper_f(get_substitutions2(strs, f), r, [r])
    end
							



(* 2. This problem involves a solitaire card game invented just for this question. You will write a program that
tracks the progress of a game; writing a game player is a challenge problem. You can do parts (a)–(e) before
understanding the game if you wish.
A game is played with a card-list and a goal. The player has a list of held-cards, initially empty. The player
makes a move by either drawing, which means removing the first card in the card-list from the card-list and
adding it to the held-cards, or discarding, which means choosing one of the held-cards to remove. The game
ends either when the player chooses to make no more moves or when the sum of the values of the held-cards
is greater than the goal.
The objective is to end the game with a low score (0 is best). Scoring works as follows: Let sum be the sum
of the values of the held-cards. If sum is greater than goal, the preliminary score is three times (sum−goal),
else the preliminary score is (goal − sum). The score is the preliminary score unless all the held-cards are
the same color, in which case the score is the preliminary score divided by 2 (and rounded down as usual
with integer division; use ML’s div operator). *)

(* you may assume that Num is always used with values 2, 3, ..., 10
   though it will not really come up *)
datatype suit = Clubs | Diamonds | Hearts | Spades
datatype rank = Jack | Queen | King | Ace | Num of int 
type card = suit * rank

datatype color = Red | Black
datatype move = Discard of card | Draw 

exception IllegalMove
	      

(* a) Write a function card_color, which takes a card and returns its color (spades and clubs are black,
diamonds and hearts are red). Note: One case-expression is enough. *)
fun card_color (s, r) = (* card => color *)
    case s of
	(Clubs | Spades) => Black
      | _ => Red


(* b) ) Write a function card_value, which takes a card and returns its value (numbered cards have their
number as the value, aces are 11, everything else is 10). Note: One case-expression is enough *)
fun card_value (s, r) = (* card => int*)
    case r of
	(Jack | Queen | King) => 10
      | Ace => 11
      | Num n => n

(* c)Write a function remove_card, which takes a list of cards cs, a card c, and an exception e. It returns a
list that has all the elements of cs except c. If c is in the list more than once, remove only the first one.
If c is not in the list, raise the exception e. You can compare cards with =. *)
fun remove_card (cs, c, e) = (* card list * card * exn => card list *)
    case cs of
	[] => raise e
      | h::t => case h = c of
		    true => t
		  | false => case remove_card(t, c, e) of
				 [] => [h]
			       | l => h::l	     
    
