#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
#include <vector>
#include <map>
#include <numeric> 
#include <algorithm>  
#include <functional> 

#include <gmpxx.h>

using namespace std;
using namespace std::chrono; 
using namespace std::placeholders; 

/**
Created on Fri Sep 04 2020
description : Find amicable pairs less than n
author      : bveitch
version     : 1.0
project     : AmicablePairs

An amicable pair is a pair of integers m,n such that the sum of proper divisors (ie excluding the number itself) of one number in the pair is equal to the other.
Ie 

s(m)=n, s(n)=m,

where s(n) denotes the sum of proper divisors.

Program should be linked with the libgmpxx and libgmp libraries. For example,
>g++ mycxxprog.cc -std=c++14 -lgmpxx -lgmp

*/

template<typename intType>
vector<intType> prime_sieve(size_t n)
{
    vector<bool> flags(n,true);
    flags[0]=false;
    auto i = static_cast<intType>(1UL);
    vector<intType> primes;
    for(auto pflag=flags.begin(); pflag != flags.end(); pflag++)
    {
        if(*pflag == true)
        {
            primes.push_back(i);
            for(auto j = i*i; j < flags.size()+1; j+=i){
                flags[j-1]=false;
            }
        }
        i++;
    }
    return primes;
}

template<typename intType>
int sum_of_divisors(intType n , const vector<intType> & primes){
    auto m=n;
    auto sigma = static_cast<intType>(1UL);
    for(const auto& p :primes)
    {
        if(m == 1) break;
        auto mult_p = static_cast<intType>(1UL);
        while( m % p == static_cast<intType>(0UL) )
        {
            m/=p;
            mult_p+=1;
        }
        if(mult_p > 1)
        {
            sigma*=(pow(p,mult_p)-1);
            sigma/=(p-1);
        }
    }
    if( m > 1) sigma*=(m+1);
        
    return (sigma - n);
}

template<typename intType>
map<intType,intType> build_divisor_map(intType N){
    auto n=ceil(sqrt(N));
     
    auto list_of_primes = prime_sieve<intType>(n);

    auto fn_sum_divisors = bind(sum_of_divisors<intType>,_1,list_of_primes); 
    
    vector<intType> ints(N);
    vector<intType> sums(N);
    
    iota (begin(ints), end(ints), 2); 
    transform(ints.begin(), ints.end(), sums.begin(), fn_sum_divisors);

    map<intType,intType> map;

    // create map
    transform(ints.begin(), ints.end(), sums.begin(), inserter(map, map.end()), [](int a, int b)
    {
        return make_pair(a, b);
    });
    return map;
}

template<typename intType>
vector< pair<intType,intType> > get_amicable_pairs(intType N){
    
    auto sigma_map = build_divisor_map<intType>(N);
    
    vector< pair<intType,intType> > amicables;

    for(const auto& i_sigma : sigma_map)
    {   
        if(i_sigma.first < i_sigma.second)
        {
            auto it=sigma_map.find(i_sigma.second);
            
            if(it != sigma_map.end() && it->second == i_sigma.first)
            {
                amicables.push_back(i_sigma);
            }
        }
	}

    return amicables; 
}
int main (int argc, char *argv[]) { 
    
    int32_t N=atoi(argv[1]);
    
    auto start = high_resolution_clock::now();

    auto amicables = get_amicable_pairs(N);
    
    auto stop = high_resolution_clock::now(); 
  
    auto duration = duration_cast<seconds>(stop - start);
    
    ofstream outfile;
    outfile.open ("listAmicablePairs_usingcpp.txt");
    outfile << "The amicable pairs less than " <<  N << " are: \n";
    for(const auto& apair: amicables){
       outfile << " (" <<  apair.first << "," << apair.second << ")\n" ;
    }
    outfile << "Runtime was " << duration.count() << " seconds\n" ;
    outfile.close();
	return 0;
}