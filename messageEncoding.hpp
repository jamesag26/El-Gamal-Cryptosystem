//
//  messageEncoding.hpp
//  ElGamal
//
//  Created by Jason  Sands on 4/19/16.
//  Copyright © 2016 James Alford-Golojuch. All rights reserved.
//

#ifndef messageEncoding_hpp
#define messageEncoding_hpp

#include <stdio.h>
#include <gmpxx.h>
#include <vector>
#include <string>

std::vector<mpz_class> getMessage(std::string message);

std::string getMessageFromInt(std::vector<mpz_class> z);

#endif /* messageEncoding_hpp */
