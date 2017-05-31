//
//  modExp.hpp
//  ElGamal
//
//  Created by James Alford-Golojuch on 4/18/16.
//  Copyright © 2016 James Alford-Golojuch. All rights reserved.
//

#ifndef modExp_hpp
#define modExp_hpp

#include <stdio.h>
#include <gmpxx.h>
#include <string>

mpz_class modExp(mpz_class a, mpz_class k, mpz_class m);

std::string intToBinary(mpz_class k);

#endif /* modExp_hpp */
