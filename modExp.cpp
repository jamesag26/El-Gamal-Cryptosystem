//
//  modExp.cpp
//  ElGamal
//
//  Created by James Alford-Golojuch on 4/18/16.
//  Copyright © 2016 James Alford-Golojuch. All rights reserved.
//

/* This module is for computing fast modular exponentiation. It takes an input of 3 large integers of a, k, m and performs modular exponentiation. It returns a big integer value final which is equivalent to (a^k)(mod m). Along with the main modular exponentiation function this module contains another function which is used by other modules. The function takes a big integer and outputs the binary value for it. For this module it is used to aid in the fast modular exponentiation function. It is also used in other modules such as the decryption module in which in takes the big integer z and returns the binary value in order for the binary string to be converted to a string of characters. 
*/
#include "modExp.hpp"
#include <gmpxx.h>
#include <string>

mpz_class modExp(mpz_class a, mpz_class k, mpz_class m)
{
    //Initialize final with value of 1 to skip needing an if statement in for loop for first string character
    //Otherwise would need to set final equal to temp in if statement
    mpz_class final = 1;
    //Binary value for exponent k
    std::string binaryNum;
    binaryNum = intToBinary(k);
    //Number of digits in binary representation of k
    size_t binSize = binaryNum.length();
    //Temp value to hold a^x(mod m) value where x is one of base 2 components of k
    mpz_class temp = a;
    //Loops through all binary digits for k
    for(size_t i = 0; i < binSize; i++)
    {
        //Multiplies a^x value into final value
        //Advances temp value to next base 2 value
        if (binaryNum[binSize - 1 - i] == '1')
        {
            final = final*temp;
            mpz_mod(final.get_mpz_t(),final.get_mpz_t(),m.get_mpz_t());
            temp = temp*temp;
            mpz_mod(temp.get_mpz_t(),temp.get_mpz_t(),m.get_mpz_t());
        }
        //Not base 2 component of k. Advances temp value to next base 2 value 
        else
        {
            temp = temp*temp;
            mpz_mod(temp.get_mpz_t(),temp.get_mpz_t(),m.get_mpz_t());
        }
    }
    return final;
}

std::string intToBinary(mpz_class k)
{
    //Gets binary value for k
    std::string binaryNum = "";
    while (k>0)
    {
        if (k%2==0)
            binaryNum = "0" + binaryNum;
        else
            binaryNum = "1" + binaryNum;
        k = k / 2;
    }
    return binaryNum;
}

