//
//  primeNum.hpp
//  ElGamal
//
//  Created by Jason  Sands on 4/18/16.
//  Copyright © 2016 James Alford-Golojuch. All rights reserved.
//

#ifndef primeNum_hpp
#define primeNum_hpp

#include <stdio.h>
#include <gmpxx.h>

mpz_class getPrime(int n, int t);

mpz_class getRandNum(int n, long seed);

bool isPrimeTest(int t, mpz_class randNum);

mpz_class getPrimitiveRoot(mpz_class p);

#endif /* primeNum_hpp */
