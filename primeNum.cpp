//
//  primeNum.cpp
//  ElGamal
//
//  Created by Jason  Sands on 4/18/16.
//  Copyright © 2016 James Alford-Golojuch. All rights reserved.
//

/* This module is for taking an input of integer n which is the desired number of bits for the length of the prime p. It also takes an input of integer t which is the level of desired confidence that the prime p is prime. This module outputs a prime number p and a primitive root g of p. There are 4 functions in this module. The first one handles the calling of the other functions associated with finding a random prime number p. It consists of a loop which gets a random number x by calling the getRandNum function and providing it with the size n and a seed to generate the random number. It tests this random number to see if its prime by calling the boolean function isPrimeTest. isPrimeTest takes input of int t for the number of trials to perform for the primality test and the random number to test primality on. It returns true if it passes every test and false if not. After getting a random number x that is prime the getPrime function also checks to see if p=2x+1 also yields a prime number and if not restarts the loop again until p is prime. This module has one more function getPrimitiveRoot which takes an input of prime p and outputs a primitive root g which is randomely generated until it passes the test of being a primitive root. 
*/

#include "primeNum.hpp"
#include "modExp.hpp"
#include <gmpxx.h>
#include <string>
#include <math.h>

mpz_class getPrime(int n, int t)
{
    //Randomly generate a number with n digits
    mpz_class randNumX;
    mpz_class randNumP;
    mpz_class primRootG;
    //Number is not prime until passes primality test
    bool isXPrime = false;
    //If X is prime tests if P is prime when p = 2x+1
    bool isPPrime = false;
    //An aditional seed to feed into the random number generator because time did not update fast enough
    //The same random number would be generated until time was incremented a changing seed value along with time helps to generate more random number
    long seed = 1;
    do {
        //Repeats test with new random number x until it passes primality test
        do {
            //Generates random number
            randNumX = getRandNum(n, seed);
            //Tests primality of random number
            isXPrime = isPrimeTest(t, randNumX);
            seed++;
        } while(!isXPrime);
        //Find prime p such that p = 2x+1
        randNumP = 2 * randNumX + 1;
        // if p=2x+1 is not prime then generate a new prime for x
        isPPrime = isPrimeTest(t, randNumP);
    } while(!isPPrime);
    return randNumP;
}

mpz_class getRandNum(int n, long seed)
{
    mpz_class randNum;
    mpz_class randFloor;
    mpz_ui_pow_ui(randFloor.get_mpz_t(), 2, n-1);
    
    //Random class will generate random number based on seed that is based on the time
    gmp_randclass randomClass(gmp_randinit_default);
    randomClass.seed(time(NULL)*seed);
    
    //Gets a random number from 0 - 2^(n-1) and adds 2^(n-1) to that random number
    //Random number is within the range 2^(n-1) - 2^n
    randNum =randomClass.get_z_range(randFloor);
    randNum = randNum + randFloor;
    
    //If randNum is even add 1 to it to make it odd
    if (randNum % 2 == 0)
        randNum = randNum + 1;
    
    return randNum;
}

bool isPrimeTest(int t, mpz_class randNum)
{
    //Assumes number is prime unless proven otherwise
    bool isPrime = true;
    //Keeps track of how many trials of primality testing
    int trials = 0;
    //Will hold values for n-1=d*2^r
    mpz_class expR, d;
    expR = 0;
    //Temp exponent for 2^R where R = i
    int i = 0;
    mpz_class temp;
    //Searches for 2^R divisor for randNum such that m is odd
    do{
        i++;
        if ((randNum - 1) % pow(2,i) == 0)
        {
            d = (randNum - 1) / pow(2,i);
            if (d % 2 == 1)
                temp = i;
        }
        else
        {
            expR = temp;
            d = (randNum - 1) / pow(2,i-1);
        }
    } while(expR == 0);
    //A seed to multiply by time to help generate more random numbers
    long seed = 1;
    //Primality test exits upon t trials being passed or number is deemed not prime
    //A primality test has been performed
    do {
        //Random int a from 1 < a < n-1
        mpz_class aRand;
        //Random class will generate random number based on seed that is based on the time
        gmp_randclass randomClass(gmp_randinit_default);
        randomClass.seed(time(NULL)*seed);
        
        //Gets a random number from 0 - (n-3) and 2 to that random number
        //Random number is within the range [2,n-2] or 1 < a < n-1
        aRand = randomClass.get_z_range(randNum - 3);
        aRand = aRand + 2;

        //Check value to determine if randNum is composite or probably prime by Miller-Rabin primality test
        mpz_class b;
        b = modExp(aRand,d,randNum);
        //If b = 1 or n-1 then we can say n is probably prime
        //isPrime is true until proven false for function. This is temporarily included for sake of code readability
        if (b == 1 || b == randNum - 1)
            isPrime = true;
        else
        {
            //Counter for loop
            int j = 0;
            //Loop stop if randNum is determined prime
            bool nextB = true;
            do{
                //Checks b again by b = b^2(mod n)
                b = modExp(b, 2, randNum);
                //If b == 1 then randNum is composite and end testing
                if (b == 1)
                {
                    isPrime = false;
                    nextB = false;
                }
                //If b == n-1 then n is probably prime and end test
                else if (b == randNum - 1)
                    nextB = false;
                //Otherwise perform another set of testing on b
                else
                    j++;
            } while (nextB && j < expR - 1);
            //Last testing will be for b when j = expR-1
            if (nextB)
            {
                b = modExp(b,2,randNum);
                if (b != randNum - 1)
                    isPrime = false;
                //isPrime is true until proven false for function. This is temporarily included for sake of code readability
                else
                    isPrime = true;
            }
        }
        //Increment seed to help generate more random numbers
        seed++;
        //One trial has been performed
        trials++;
    } while(isPrime && trials < t/2);
    return isPrime;
}

mpz_class getPrimitiveRoot(mpz_class p)
{
    mpz_class primRoot, test;
    mpz_class x = (p-1)/2;
    bool isPrimRoot = false;
    //Similiar as past seeds helps generate better random numbers due to it changing with each new random number needed
    long seed = 1;
    //Random class will generate random number based on seed that is based on the time
    gmp_randclass randomClass(gmp_randinit_default);
    
    do{
        randomClass.seed(time(NULL)*seed);
        //Gets a random number from 0 - p-3 and adds 2 to that random number
        //Random number is within the range 2 - (p-1) or 2 <= primRoot < p
        primRoot =randomClass.get_z_range(p-2);
        primRoot = primRoot + 2;
    
        //We know x is a prime and that prime p=2x+1
        //The factor of (p-1)=2x are 2 and prime x
        //Get value for primroot g for g^((p-1)/q)(mod p) where q represents the factors of p-1 which from above are x and 2
        //If those values are not 1 for both factors then g is a primRoot
        //Else generate a new primRoot
        test = modExp(primRoot,(p-1)/2 ,p);
        if (test != 1)
        {
            test = modExp(primRoot, (p-1)/x, p);
            if (test != 1)
                isPrimRoot = true;
        }
        //Increment seed
        seed++;
    }while(!isPrimRoot);
    return primRoot;
}