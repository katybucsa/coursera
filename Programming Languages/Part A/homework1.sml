
fun is_older (date1 : (int*int*int), date2 : (int*int*int)) = (* (year, month, day) *)

    if #1 date1 < #1 date2
    then true
    else if #1 date1 > #1 date2
    then false
    else if #2 date1 < #2 date2
    then true
    else if #2 date1 > #2 date2
    then false
    else if #3 date1 < #3 date2
    then true
    else false


fun number_in_month (dates : (int*int*int) list, month : int) =

    if null dates
    then 0
    else if #2 (hd dates) = month
    then 1 + number_in_month(tl dates, month)
    else number_in_month(tl dates, month)


fun number_in_months (dates : (int*int*int) list, months : int list) =

    if null dates orelse null months
    then 0
    else number_in_month( dates, hd months) + number_in_months(dates, tl months)


fun dates_in_month (dates : (int*int*int) list, month : int) =

    if null dates
    then []
    else if #2 (hd dates) = month
    then (hd dates)::dates_in_month(tl dates, month)
    else dates_in_month(tl dates, month)
		       
							      
fun dates_in_months (dates : (int*int*int) list, months : int list) =

    if null dates orelse null months
    then []
    else dates_in_month(dates, hd months)@dates_in_months(dates, tl months)
							 

fun get_nth (strings : string list, n : int) =

    if n = 1
    then hd strings
    else get_nth(tl strings, n-1)



fun date_to_string (date : (int*int*int)) =

    let
	val months = [ "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    in
	get_nth(months, #2 date)^ " " ^ Int.toString(#3 date) ^ ", " ^ Int.toString(#1 date)
										   
    end
	

	
fun number_before_reaching_sum (sum : int , numbers : int list) = (* int*(int list)-->int ; sum >=0, numbers are also positive*)

    if null numbers orelse sum - hd numbers <= 0 
    then 0
    else 1 + number_before_reaching_sum(sum - hd numbers, tl numbers)
	     


fun what_month (day : int) = (* day of year: 1:365 *)

    let
	val months = [31,28,31,30,31,30,31,31,30,31,30,31]
    in
	1+number_before_reaching_sum(day,months)
    end

	
fun month_range (day1 : int, day2 : int) =

    if day1 > day2
    then []
    else what_month(day1) :: month_range(day1 + 1, day2)
				      


fun oldest (dates : (int*int*int) list) =

    if null dates
    then NONE
    else
	let
	    fun oldest_nonempty (dates : (int*int*int) list) =
		if null (tl dates)
		then hd dates
		else let val date = oldest_nonempty(tl dates)
		     in
			 if is_older(hd dates, date)
			 then hd dates
			 else date
		     end
	in
	    SOME(oldest_nonempty dates)
	end



fun elem_in_list (elem : int, l: int list) =

    if null l
    then false
    else if elem = hd l
    then true
    else elem_in_list(elem, tl l)

		     

fun eliminate_duplicates (months : int list) =

    if null months
    then []
    else
	let
	    val l = eliminate_duplicates(tl months)
	in
	    if elem_in_list(hd months, l)
	    then l
	    else (hd months)::l
	end


	    
fun number_in_months_challenge (dates : (int*int*int) list, months: int list) =

    number_in_months(dates, eliminate_duplicates(months))



fun dates_in_months_challenge (dates: (int*int*int) list, months: int list) =

    dates_in_months(dates, eliminate_duplicates(months))
		   
	    


fun get_nth_int (ints : int list, n : int) =

    if n = 1
    then hd ints
    else get_nth_int(tl ints, n-1)
		

fun resonable_date (date : int*int*int) =

    if #1 date < 1 orelse #2 date < 1 orelse #2 date > 12 orelse #3 date <1 orelse #3 date >31
    then false
    else
	let
	    val months1 = [31,28,31,30,31,30,31,31,30,31,30,31]
	    val months2 = [31,29,31,30,31,30,31,31,30,31,30,31]
	in
	    if (#1 date mod 4 = 0 andalso #1 date mod 100 <> 0) orelse #1 date mod 400 = 0
	    then #3 date <= get_nth_int(months2, #2 date)
	    else #3 date <= get_nth_int(months1, #2 date)
	end



	    (* EXTRA PRACTICE PROBLEMS *)


(* 1 *)
fun alternate_wrapper (numbers : int list, sign : string) =

    if null numbers
    then 0
    else if sign = "+"
    then hd numbers + alternate_wrapper(tl numbers, "-")
    else ~(hd numbers) + alternate_wrapper(tl numbers, "+")
				       
	    
	    
fun alternate (numbers: int list) = (* int list --> int *)

    if null numbers
    then 0
    else alternate_wrapper(numbers, "+")


			  
(* 2 *)	    
fun min_max (numbers : int list) = (* int lit --> int * int *)

    if null numbers
    then NONE
    else
	let
	    fun min_max_nonempty(numbers : int list) =

		if null (tl numbers)
		then (hd numbers, hd numbers)
		else
		    let
			val mm = min_max_nonempty(tl numbers)
		    in
			if hd numbers < #1 mm
			then (hd numbers, #2 mm)
			else if hd numbers > #2 mm
			then (#1 mm, hd numbers)
			else mm
		    end
	in
	SOME(min_max_nonempty numbers)				      
	end




(* 3 *)
fun last_elem ( elems : int list) = (* the last elem of the list *)

    if null (tl elems)
    then hd elems
    else last_elem(tl elems)

		  
fun cumsum_wrapper (numbers: int list, sum_l : int list) =

    if null numbers
    then sum_l
    else cumsum_wrapper(tl numbers, sum_l @ [hd numbers + last_elem(sum_l)])

				      
fun cumsum (numbers : int list) = (* int list --> int list *)

    if null numbers
    then []
    else cumsum_wrapper(tl numbers, [hd numbers])


		       
(* 4 *)
fun greeting (name: string option) =

    if isSome name
    then "Hello there, " ^ valOf name ^ "!"
    else "Hello there, you"



(* 5 *)
fun repeat (numbers : int list, repetitions : int list) =

    if null numbers
    then []
    else if hd repetitions > 0
    then hd numbers::repeat(numbers, hd repetitions - 1::tl repetitions)
    else repeat(tl numbers, tl repetitions)



(* 6 *)
fun addOpt (n1 : int option, n2 : int option) =

    if isSome n1 andalso isSome n2
    then SOME(valOf n1 + valOf n2)
    else NONE
	     
	       
			   
(* 7 *)	     
fun addAllOpt (numOpt : int option list) =

    if null numOpt
    then NONE
    else
	let
	    val sum = addAllOpt(tl numOpt)
	in
	    if isSome (hd numOpt) andalso isSome sum
	    then SOME (valOf (hd numOpt) + valOf sum)
	    else if isSome (hd numOpt)
	    then hd numOpt
	    else if isSome sum
	    then sum
	    else NONE 
	end
		  


(* 8 *)
fun any (booleans : bool list) =

    if null booleans
    then false
    else if hd booleans
    then true
    else any(tl booleans)



(* 9 *)
fun all (booleans : bool list) =

    if null booleans
    then true
    else if not (hd booleans)
    then false
    else all(tl booleans)



(* 10 *)
fun zip (l1 : int list, l2 : int list) =

    if null l1 orelse null l2
    then []
    else (hd l1, hd l2)::zip(tl l1, tl l2)


(* 11 *)
fun zipRecycle (l1 : int list, l2 : int list) =

    if null l1 orelse null l2
    then []
    else
	let
	    fun zip(list1 : int list, list2 : int list, l1b : bool, l2b : bool) =

		if (l1b andalso l2b) orelse ( null list1 andalso null list2)
		then []
		else if null list1
		then zip(l1, list2, true, l2b)
		else if null list2
		then zip(list1, l2, l1b, true)
		else (hd list1, hd list2)::zip(tl list1, tl list2, l1b, l2b)
					      
	in
	    zip(l1,l2, false, false)
	end
	    


(* 12 *)			    
fun zipOpt (l1 : int list, l2 : int list) =

    if (null l1 andalso not (null l2)) orelse (null l2 andalso not (null l1))
    then NONE
    else if null l1 andalso null l2
    then SOME([])
    else
	let
	    val res = zipOpt(tl l1, tl l2)
	in
	    if isSome res
	    then SOME((hd l1, hd l2) :: valOf res)
	    else NONE
	end
	    

(* 13 *)
fun lookup (pairs : (string * int) list, s : string) =

    if null pairs
    then NONE
    else if #1 (hd pairs) = s
    then SOME(#2 (hd pairs))
    else lookup(tl pairs, s)



(* 14 *)
fun splitup (numbers : int list) =


    if null numbers
    then ([],[])
    else
	let
	    val res = splitup(tl numbers)
	in
	    if hd numbers >= 0
	    then ((hd numbers):: #1 res, #2 res)
	    else (#1 res, (hd numbers):: #2 res)
	end
	    


(* 15 *)
fun splitAt (numbers : int list, n : int) =

    if null numbers
    then ([],[])
    else
	let
	    val res = splitAt(tl numbers, n)
	in
	    if hd numbers >= n
	    then ((hd numbers):: #1 res, #2 res)
	    else (#1 res, (hd numbers):: #2 res)
	end



(* 16 *)	    
fun isSorted (numbers : int list) =

    if null numbers orelse null (tl numbers)
    then true
    else if hd numbers > hd (tl numbers)
    then false
    else isSorted(tl numbers)



(* 17 *)
fun isSortedDesc (numbers : int list) =

    if null numbers orelse null (tl numbers)
    then true
    else if hd numbers < hd (tl numbers)
    then false
    else isSortedDesc(tl numbers)

		 
fun isAnySorted (numbers : int list) =

    if isSorted(numbers) orelse isSortedDesc(numbers)
    then true
    else false
	     

(* 18 *)
fun sortedMerge (l1 : int list, l2 : int list) =

    if null l1
    then l2
    else if null l2
    then l1
    else if hd l1 < hd l2
    then (hd l1) :: sortedMerge(tl l1, l2)
    else (hd l2) :: sortedMerge(l1, tl l2)

			      
		 
(* 19 *)
fun qsort (l : int list) =

    if null l
    then []
    else
	let
	    val splitted = splitAt(tl l, hd l)
	    val l1 = qsort(#1 splitted)
	    val l2 = qsort(#2 splitted)
	in
	    l2 @ (hd l :: l1)
	end


(* 20 *)
fun divide (numbers : int list) =


    if null numbers
    then ([],[])
    else if null (tl numbers)
    then ([hd numbers],[])
    else
	let
	    val res = divide(tl (tl numbers))
	in
	    ((hd numbers) :: #1 res, hd (tl numbers) :: #2 res)
	end
	    

(* 21 *)
fun not_so_quick_sort (numbers : int list) =

    if null numbers
    then []
    else if null (tl numbers)
    then [hd numbers]
    else
	let
	    val divided = divide(numbers)
	    val l1 = not_so_quick_sort(#1 divided)
	    val l2 = not_so_quick_sort(#2 divided)
	in
	    sortedMerge(l1, l2)
	end
	    

(* 22 *)
fun fullDivide (k : int, n : int) =

    if n mod k <> 0
    then (0, n)
    else
	let
	    val res = fullDivide(k, n div k)
	in
	    (#1 res + 1, #2 res)
	end
	    


(* 23 *)
fun factorize (n : int) =

    if n < 1
    then []
    else
	let
	    fun fact (n : int, d : int) =

		if n = 1
		then []
		else if d * d > n
		then [(n,1)]
		else
		    let
			val res = fullDivide(d, n) 
		    in
			if #1 res = 0
			then fact(n, d + 1)
			else (d, #1 res) :: fact(#2 res, d + 1)
		    end
	in
	    fact(n, 2)
	end
	    

(* 24 *)	    
fun multiply (fact_l : (int*int) list) =

    if null fact_l
    then 1
    else if #2 (hd fact_l) <> 0
    then #1 (hd fact_l) * multiply ((#1 (hd fact_l),#2 (hd fact_l)-1) :: (tl fact_l))
    else multiply(tl fact_l)
	     

(* 25 *)
fun one_factor (p : int* int) =

    if #2 p = 0
    then [1]
    else
	let
	    val res = one_factor((#1 p, #2 p - 1))
	in
	    (#1 p * hd res) :: res
	end


fun two_product (l1 : int list, l2 : int list)  =

    if null l1
    then []
    else
	let
	    fun prod ( li1 : int list, li2 : int list) =

		if null li1
		then []
		else if null li2
		then prod(tl li1, l2)
		else
		    let
			val res = prod(li1, tl li2)
		    in
			(hd li1 * hd li2) :: res
		    end
	in
	    prod(l1, l2)
	end
	    
	    
fun all_products ( l : (int*int) list) =

    if null l
    then []
    else
	let
	    val res = all_products(tl l)
	    val one_product = one_factor(hd l)
	in
	    if null res
	    then qsort(one_product)
	    else qsort(two_product(one_product, res))
	end
	    
	    


	    
