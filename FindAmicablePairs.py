#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Aug 27 18:59:24 2020
description : Find amicable pairs less than n
author      : bveitch
version     : 1.0
project     : AmicablePairs

An amicable pair is a pair of integers m,n such that the sum of proper divisors (ie excluding the number itself) of one number in the pair is equal to the other.
Ie 

s(m)=n, s(n)=m,

where s(n) denotes the sum of proper divisors.
"""

from functools import partial

def prime_sieve(n):
    primes=[True]*n
    primes[0]=False
    for p in range(2,len(primes)):
        is_a_p=primes[p-1]
        if(is_a_p):
            for j in range(p*p,n,p):
                primes[j-1]=False
    list_of_primes=[j for j in range(2,n) if primes[j-1]==True]
    return list_of_primes
            
def sum_of_divisors(list_of_primes,n):
    m=n
    sigma=1
    for p in list_of_primes:
        mult_p=1
        while(m % p == 0):
            m/=p
            mult_p+=1
        if(mult_p > 1):
            sigma*=((p**mult_p)-1)
            sigma/=(p-1)
    if(m > 1):
        sigma+=m
    return (int(sigma) - n) 

def divisor_dict(n,sum_of_divisors_fn):
    candidates=[i for i in range(2,n)]
    sigmas=[sum_of_divisors_fn(c) for c in candidates]
    return dict(zip(candidates, sigmas))
        
        
n=1000000
list_of_primes=prime_sieve(n)
sigma_fn=partial(sum_of_divisors,list_of_primes)
sigma_dict=divisor_dict(n,sigma_fn)
amicables=[]
for i,s in sigma_dict.items():
    if(s,i) in sigma_dict.items():
        if(i < s): 
            amicables.append([i,s])

outF = open("listAmicablePairs.txt", "w") 
outF.write('The amicable pairs less than {} are'.format(n))
outF.write("\n")
for i,j in amicables:
   print((i,j))  
   outF.write(' {:} , {:}'.format(i,j))
   outF.write("\n")
outF.close()

            
    
        
