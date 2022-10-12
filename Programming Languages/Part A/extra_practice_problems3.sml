(* 1.  Write a function compose_opt : ('b -> 'c option) -> ('a -> 'b option) -> 'a -> 'c option|compose_opt : (’b -> ’c option) -> (’a -> ’b option) -> ’a -> ’c option that composes two functions with "optional" values. If either function returns \verb|NONE|NONE, then the result is \verb|NONE|NONE. *)

fun compose_opt f g x =
    let
	val r = g x
    in
	case r of
	    NONE => NONE
	  | _ => f r 
    end



(* 2. Write a function do_until : ('a -> 'a) -> ('a -> bool) -> 'a -> 'a. do_until f p x will apply f to x and f again to that result and so on until p x is false.  Example: do_until (fn x => x div 2) (fn x => x mod 2 <> 1) will evaluate to a function of type int->int that divides its argument by 2 until it reaches an odd number. In effect, it will remove all factors of 2 its argument. *)

fun do_until f p x =
    case p x of
	false => x
      | true => do_until f p (f x)



(* 3. Use do_until to implement factorial. *)

fun fact el =
    let
	val res = do_until (fn x => ((#1 x) - 1,(#1 x) * (#2 x))) (fn x => #1 x > 1) (el, 1)
    in
	#2 res
    end
