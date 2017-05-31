//
//  messageEncoding.cpp
//  ElGamal
//
//  Created by Jason  Sands on 4/19/16.
//  Copyright © 2016 James Alford-Golojuch. All rights reserved.
//

/* This module is for the encoding and decoding of the message from a string to a big integer. This module takes an input of a string message and converts it into a big int of size 2^200 bits. It takes every 25 characters of the string or less, if there is less than 25 or number not divisible by 25, for the final integer. Since each character is 8 bits long and n is 200 bits this enables the program to put 25 characters into the formation of one big integer. It returns an array of these big integers in which every character has been accounted for in a big int in the vector. It also has another function in which it converts an array of big integers, z, into a string message. This is especially useful for the decoding phase of the El Gamal system.
*/

#include "messageEncoding.hpp"
#include "modExp.hpp"
#include <gmpxx.h>
#include <string>
#include <bitset>
#include <vector>

std::vector<mpz_class> getMessage(std::string message)
{
    //Binary represenation of parts of the message
    std::string bits = "";
    //A vector holding integers representing 25 8 bit characters
    std::vector<mpz_class> z;
    //Temp value to hold int value before storing in vector z
    mpz_class temp;
    //Takes binary representation of 25 characters and gets int value for it. Places int value into a vector
    for (int i=0; i < message.length(); i++)
    {
        if ( i % 25 == 0 && i != 0)
        {
            temp.set_str(bits, 2);
            z.push_back(temp);
            bits = "";
        }
        std::bitset<8> mBits = (message[i]);
        bits = bits + mBits.to_string();
    }
    //Converts remaining (if < 25) characters binary rep into an int value and adds it to the vector
    temp.set_str(bits, 2);
    z.push_back(temp);
    return z;
}

std::string getMessageFromInt(std::vector<mpz_class> z)
{
    //Holds message
    std::string message = "";
    //Holds binary representation for integers in vector  z
    std::string bin;
    for(int i=0; i < z.size(); i++)
    {
        bin = intToBinary(z[i]);
        //Check to make sure each character will have 8 bits as leading 0's may have been cut off
        //Adds leading 0's until every character will have 8 bits
        while(bin.length() % 8 != 0)
            bin = "0" + bin;
        for(int j=0; j < (bin.length()/8); j++)
        {
            std::string temp (bin, j*8, 8);
            std::bitset<8> charBit = (0);
            //Sets each bit for converting from string temp to a bitset
            //Had to set bitset in reverse due to how bits were stored vs how they need to be read to char
            for(int k=0; k < 8; k++)
            {
                if (temp[k] == '1')
                    charBit.set(7-k, 1);
            }
            //Add character to message
            message = message + char(charBit.to_ulong());
        }
    }
    return message;
}