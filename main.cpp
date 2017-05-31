//
//  main.cpp
//  ElGamal
//
//  Created by James Alford-Golojuch on 4/17/16.
//  Copyright © 2016 James Alford-Golojuch. All rights reserved.
//

/* Main module which recieves the user input for the desired n and t values and calls the different modules of the El Gamal system which generates the encryption and decryption keys along with encrypting and decrypting a user message. 
*/

#include <gmpxx.h>
#include "keyGeneration.hpp"
#include "encryptMessage.hpp"
#include "decryptMessage.hpp"
#include <iostream>


int main(int argc, const char * argv[]) {
    int t, n;
    std::cout << "How many n-bits would you like the prime number to be?" << std::endl;
    std::cin >> n;
    std::cout << std::endl;
    std::cout << "What would you like the desired confidence that p is prime to be?" << std::endl;
    std::cin >> t;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    generateKeys(n, t);
    encryptM();
    decodeCipher();
    return 0;
}
