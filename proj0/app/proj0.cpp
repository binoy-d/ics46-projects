#include <map>
#include <string>
#include "proj0.hpp"


bool verifySolution(std::string s1, std::string s2, std::string s3, const std::map<char, unsigned> & mapping)
{
    unsigned int carry  = 0;
    for(unsigned int i = s3.length(); i>=0; --i){
        
        unsigned int num1 = mapping.at(s1[i]);
        unsigned int num2 = mapping.at(s2[i]);



        unsigned int result = mapping.at(s3[i]);
        if((num1+num2+carry)%10!=result){
            return false;
        }else{
            //set carry to 10's place
            carry = (num1+num2+carry)/10;
        }

    }
    return true; // FYI, this stub is not a correct solution.
}





