//
//  decryptMessage.cpp
//  ElGamal
//
//  Created by Jason  Sands on 4/20/16.
//  Copyright © 2016 James Alford-Golojuch. All rights reserved.
//

/* This module is focused on the decryption of the cipher text which was the ouput form the encryptMessage module. It reads the pais of big integers from that file along with the private key K2 from the K2 file. Using the private key and the big integers it decrypts the big integer pair from the cipher text before then converting it to a binary string through a call to the intToBinary function from the modExp module, and then finally it converts that binary string into a string of characters which was the message before encryption. This module outputs that now decrypted message to a plaintext file. 
*/

#include "decryptMessage.hpp"
#include "messageEncoding.hpp"
#include "modExp.hpp"
#include <gmpxx.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void decodeCipher()
{
    //Will hold the decoded message
    std::string message = "";
    //Vector of integer values z for parts of message m to be calculated from cipher text pairs
    std::vector<mpz_class> z;
    //Key values for K2 (p,g,x)
    mpz_class p, g, x;
    //Reads K2 file
    std::fstream file;
    file.open("/Users/jasonsands/Desktop/ElGamal/ElGamal/ElGamal/K2.txt", std::fstream::in);
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
        //Reads third line which is the integer x
        std::getline(file, temp);
        x = temp;
    }
    //Temp strings to read from file and hold values
    std::string temp;
    std::string mpzString;
    //Holds values for integer pair c,d from cipher text
    mpz_class  c, d;
    //Holds values for s (s=c^x(mod p))
    mpz_class s;
    //Reads cipher text file
    std::fstream cipherText;
    cipherText.open("/Users/jasonsands/Desktop/ElGamal/ElGamal/ElGamal/cipher.txt", std::fstream::in);
    //Shows error when opening file during testing
    if (!cipherText)
        std::cout << "Error file couldn't be opened" << std::endl;
    else
    {
        while(getline(cipherText, temp))
        {
            //Distributes two integers from line to c and d
            std::stringstream linestream(temp);
            
            getline(linestream, mpzString, ',');
            c = mpzString;
            getline(linestream, mpzString);
            d = mpzString;
            //Gets value for s where s=(c^x)(mod p)
            s = modExp(c, x, p);
            //Adds integer z to vector where z=d*s^(p-2)(mod p)
            d = d * modExp(s, p-2, p);
            mpz_mod(d.get_mpz_t(),d.get_mpz_t(),p.get_mpz_t());
            z.push_back(d);
        }
        message = getMessageFromInt(z);
        
        //Writes message to plaintext file
        std::fstream plainText;
        plainText.open("/Users/jasonsands/Desktop/ElGamal/ElGamal/ElGamal/plain.txt", std::fstream::out | std::fstream::trunc);
        //Shows error when opening file during testing
        if (!plainText)
            std::cout << "Error file couldn't be opened" << std::endl;
        else
            plainText << message;
    }
}