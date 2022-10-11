(* 1.  Write a function compose_opt : ('b -> 'c option) -> ('a -> 'b option) -> 'a -> 'c option|compose_opt : (’b -> ’c option) -> (’a -> ’b option) -> ’a -> ’c option that composes two functions with "optional" values. If either function returns \verb|NONE|NONE, then the result is \verb|NONE|NONE. *)

fun compose_opt f g x =
    let
	val r = g x
    in
	case r of
	    NONE => NONE
	  | _ => f r 
    end



(* 2. Write a function \verb|do_until : ('a -> 'a) -> ('a -> bool) -> 'a -> 'a|do_until : (’a -> ’a) -> (’a -> bool) -> ’a -> ’a.   \verb|do_until f p x|do_until f p x will apply \verb|f to x|f to x and \verb|f|f again to that result and so on until \verb|p x|p x is \verb|false|false.  Example: \verb|do_until (fn x => x div 2) (fn x => x mod 2 <> 1)|do_until (fn x => x div 2) (fn x => x mod 2 <> 1) will evaluate to a function of type \verb|int->int|int->int that divides its argument by \verb|2|2 until it reaches an odd number. In effect, it will remove all factors of \verb|2|2 its argument. *)

fun do_until f p x =
    case p x of
	false => x
      | true => do_until f p (f x)

