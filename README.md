# AmicablePairs

An amicable pair is a pair of integers m,n such that
the sum of proper divisors (ie excluding the number itself) of one number in the pair, is equal to the other.
Ie 

s(m)=n, s(n)=m,

where s(n) denotes the sum of proper divisors.

If &sigma;(n) denotes the sum of all divisors of a number (ie including the number itself) and 

n = Product_{p=primes dividing n} (p^a_p),

where a_p is the multiplicity of p as a divisor of n, then,

&sigma(n)=Product_{p=primes dividing n} (p^(a_p+1) -1)/(p-1),

and s(n) = &sigma(n)-n.

So, given a list of primes (say, using sieve of Erathothenes), computing s(n) can be relatively efficient.

The code then computes a list of s(n)'s for a range of integers < n.

Finally, finding amicable pairs is now an exercise in using Python's dictionary methods on {n,s(n)}.

For C++ implementation an unordered_map (Hash table) is used to  give O(1) lookup time.
