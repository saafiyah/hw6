#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				int len = k.size();
        HASH_INDEX_T v[5] = {0, 0, 0, 0, 0};
				for(int i = 0; i < len/6+1; i++)
				{
					unsigned long long total = 0;
					for(int j= 0 ; j < 6; j++)
					{
						if(len - (i+1)*6 + j >= 0)
						{
							total = 36*total + letterDigitToNumber(k[len - (i+1)*6 +j]);
						}
					}
					v[5-i-1] = total;
				}
				unsigned long long retval = 0; 
				for(int i = 0; i < 5; i++)
				{
					retval += rValues[i]*v[i];
				}
				return retval; 
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter < 58)
				{
					return letter - 22;
				}
				else if(letter < 91)
				{
					return letter - 65;
				}
				else
				{
					return letter - 97;
				}
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
