//
//  main.cpp
//  Primes using factorization
//
//  Created by Simone Cimolato on 02/04/17.
//  Copyright © 2017 Simone Cimolato. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<long> primes;
__int128_t sum = 2;
unsigned long long counter = 4;
bool Sum;

typedef __int128 int128_t;

/*      UINT64_MAX 18446744073709551615ULL */
#define P10_UINT64 10000000000000000000ULL   /* 19 zeroes */
#define E10_UINT64 19

#define STRINGIZER(x)   # x
#define TO_STRING(x)    STRINGIZER(x)

std::ostream&
operator<<(std::ostream& dest, __int128_t value){
    std::ostream::sentry s(dest);
    if (s){
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char* d = std::end(buffer);
        do{
            -- d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);
        if (value < 0) {
            -- d;
            *d = '-';
        }
        long len = std::end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len) {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

int isPrime(unsigned long long number);
long SumOfPrimes(vector<long> primes);
void print(vector<long> primes);

int main(int argc, const char * argv[]) {
    
    //must be > 8
    unsigned long long lastOne = 0;
    cout<<"Last number to check: ";
    cin>>lastOne;
    
    if (cin.fail() or lastOne < 9) {
        cout<<"Must be an integer number greater than 8."<<endl;
        return 1;
    }
    
    //Here i'm using the Prime Number Theorem
    cout<<endl<<"About "<<(1/log(lastOne))*100<<"% of numbers less than "<<lastOne<<" are prime."<<endl
        <<"There are about: "<<round(lastOne/log(lastOne))<<" primes between 0 and "<<lastOne<<endl
        <<"Estimated average gap between prime numbers: "<<log(lastOne)<<endl
        <<"Computing..."<<endl<<endl;
    
    primes.push_back(3);
    primes.push_back(5);
    primes.push_back(7);

    clock_t start = clock();
    
    /*
     k starts from 9 because in the isPrime function i check
     if k is a multiple of 2,3,5,7 and if it is, then k is not prime, but 2,3,5,7 are actually primes, so if
     k was 2,3,5 or 7 then it wouldn't be counted as prime
     */
    
    for (int k = 9; k <= lastOne; k+=2){
        isPrime(k);
    }
    
    clock_t end = clock();
    double time = (double) (end-start) / CLOCKS_PER_SEC;
    
    //printing
    print(primes);
        
    cout<<endl<<endl<<"Initial estimate of the percentage of prime numbers: "<<round(lastOne/log(lastOne))<<endl
        <<"Real number of primes: "<<counter<<endl
        <<time<<" seconds to calculate the primes."<<endl<<endl
        <<"Initial estimate of primes less than "<<lastOne<<": "<<(1/log(lastOne))*100<<"%"<<endl
        <<"Real percentage: "<<((double)counter/(double)lastOne)*100.0<<"%"<<endl<<endl;                          //counter rimane a 0, strano  PROBLEMS!!!!

    //sum
    SumOfPrimes(primes);
    
    return 0;
}


int isPrime(unsigned long long number){
    //square root
    unsigned long long max = ceil(sqrt(number));
    for (unsigned long long i = 0; primes[i] <= max; i++){
        if (number % primes[i] == 0) return 0;  //not prime
    }
    
    //prime
    primes.push_back(number);
    counter++;
    
    return 0;
}

long SumOfPrimes(vector<long> primes){
    clock_t Bsum = clock();
    for (int t = 0; t < primes.size(); t++) {
        sum+=primes[t];
    }
    
    clock_t Esum = clock();
    double timeSum = (double) (Esum-Bsum) / CLOCKS_PER_SEC;
    cout<<"Sum of all primes: "<<sum<<endl
        <<timeSum<<" seconds to sum the primes."<<endl<<endl;
    return 0;
}

//print function
void print(vector<long> primes){
    cout<<"2, ";
    for (unsigned long long i = 0; i < primes.size(); i++){
        cout<<primes[i]<<", ";
    }
}
