//
//  keyGeneration.cpp
//  ElGamal
//
//  Created by Jason  Sands on 4/20/16.
//  Copyright © 2016 James Alford-Golojuch. All rights reserved.
//

/* This module takes the input of an integer n for the desired number of bits and t for the desired confidence of the primality test. It passes these values onto the primeNum function in order to generate a prime number p and its primitive root g. It also generates a random big integer x and gets a value for big integer h which is equivalent to (g^x)(mod p). These 4 big integers form the private and public keys which are the output for this module by being written to files K1 and K2 where K1 is the public key containing the values (p,g,h) and where K2 is the private key containing the big integer values of (p,g,x). 
*/

#include "keyGeneration.hpp"
#include "primeNum.hpp"
#include "modExp.hpp"
#include <gmpxx.h>
#include <fstream>
#include <iostream>

void generateKeys(int n, int t)
{
    //Prime p and its primitive root g, random number x and integer h which is h=(g^x)(mod p)
    mpz_class p, g, x, h;
    //Gets prime number for p
    p = getPrime(n, t);
    //Gets primitive root of p for g
    g = getPrimitiveRoot(p);
    
    //Gets random number x in range 1 <= x < p
    //Random class will generate random number based on seed that is based on the time * p to make numbers more random
    gmp_randclass randomClass(gmp_randinit_default);
    randomClass.seed(time(NULL)*p);
    
    //Gets a random number from 0 <= x < (p-1) and adds 1 to that random number
    //Random number is within the range 1 <= x < p
    x = randomClass.get_z_range(p-1);
    x = x + 1;
    
    //Gets value for h where h=(g^x)(mod p)
    h = modExp(g, x, p);
    //Creates and writes to a file public key K1 (p,g,h)
    std::fstream file;
    file.open("/Users/jasonsands/Desktop/ElGamal/ElGamal/ElGamal/K1.txt", std::fstream::out | std::fstream::trunc);
    //Shows error when opening file during testing
    if (!file)
        std::cout << "Error" << std::endl;
    else
    {
        file << p << std::endl;
        file << g << std::endl;
        file << h << std::endl;
    }
    file.close();
    
    //Creates and writes to a file public key K2 (p,g,x)
    std::fstream file2;
    file2.open("/Users/jasonsands/Desktop/ElGamal/ElGamal/ElGamal/K2.txt", std::fstream::out | std::fstream::trunc);
    //Shows error when opening file during testing
    if (!file2)
        std::cout << "Error" << std::endl;
    else
    {
        file2 << p << std::endl;
        file2 << g << std::endl;
        file2 << x << std::endl;
    }
    file2.close();

}