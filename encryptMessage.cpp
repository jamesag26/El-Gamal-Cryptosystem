//
//  encryptMessage.cpp
//  ElGamal
//
//  Created by Jason  Sands on 4/20/16.
//  Copyright © 2016 James Alford-Golojuch. All rights reserved.
//

/* This module is focused on the encryption of a user input string message. It takes the input of the user message and reads the public key from file K1. Using the public key and the string message it converts the string message into a vector of big integers and then encodes those big integers through the El Gamal encryption function. It then outputs a pair of big integers for each big integer z in vector z.   
*/

#include "encryptMessage.hpp"
#include "messageEncoding.hpp"
#include "modExp.hpp"
#include <gmpxx.h>
#include <iostream>
#include <fstream>
#include <vector>

void encryptM()
{
    //Will hold the message
    std::string message;
    //Vector of integer values z for parts of message m
    std::vector<mpz_class> z;
    //Key values for K1 (p,g,h)
    mpz_class p, g, h;
    //Reads K1 file
    std::fstream file;
    file.open("/Users/jasonsands/Desktop/ElGamal/ElGamal/ElGamal/K1.txt", std::fstream::in);
    //Shows error when opening file during testing
    if (!file)
        std::cout << "Error file couldn't be opened" << std::endl;
    else
    {
        std::string temp;
        //Reads first line which is prime number p
        std::getline(file, temp);
        p = temp;
        //Reads second line which is primitive root g
        std::getline(file, temp);
        g = temp;
        //Reads third line which is the integer h
        std::getline(file, temp);
        h = temp;
    }
    
    std::cout << "What is your message?" << std::endl;
    std::getline(std::cin, message);
    //Gets integer values z for the message
    z = getMessage(message);
    //Random number y
    mpz_class y;
    //initialize random class
    gmp_randclass randomClass(gmp_randinit_default);
    //Opens file to write cipher pairs to
    std::fstream cipher;
    cipher.open("/Users/jasonsands/Desktop/ElGamal/ElGamal/ElGamal/cipher.txt", std::fstream::out | std::fstream::trunc);
    //Encrypts each integer z
    for(int i=0; i < z.size(); i++)
    {
        //Will generate random number based on seed that is based on the time * z[i]to make numbers more random
        randomClass.seed(time(NULL)*z[i]);
        //Gets a random number from 0 <= y < p
        y = randomClass.get_z_range(p);
        //Encrypted integers for z to be stored into cipher text
        mpz_class c, d;
        c = modExp(g, y, p);
        d = modExp(h, y, p) * z[i];
        mpz_mod(d.get_mpz_t(), d.get_mpz_t(), p.get_mpz_t());
        cipher << c << "," << d << std::endl;
    }
}
