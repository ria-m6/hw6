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
        std::vector<HASH_INDEX_T> w(5,0);
        int wIndex =4;

        int len = k.size();
        for(int i = len; i>0; i -= 6){
            HASH_INDEX_T value = 0;
            int start = (i>=6 ? i-6 : 0);

            for(int j = start; j<i;j++){
                value = value * 36 +letterDigitToNumber(k[j]);
            }
            w[wIndex--] = value;
        }

        HASH_INDEX_T hashResult = 0;
        for(int i =0; i< 5; i++){
            hashResult += rValues[i] * w[i];
        }
        return hashResult;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(std::isdigit(letter)){
            return letter - '0' +26;
        } else{
            return std::tolower(letter) - 'a';
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
