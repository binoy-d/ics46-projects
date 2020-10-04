#include <map>
#include <string>
#include <iostream>
#include "proj0.hpp"


bool verifySolution(std::string s1, std::string s2, std::string s3, const std::map<char, unsigned> & mapping)
{
    bool debug = false;

    if(debug)std::cout<<"\n\n\n"<<s1<<" + "<<s2<<" = "<<s3<<"\n\n";
    if(s3.length()<s1.length() || s3.length()<s2.length()) return false;

    unsigned int carry  = 0;
    for(unsigned int i = 0; i<s3.length(); ++i){
        int index1 = s1.length()-i-1;
        int index2 = s2.length()-i-1;
        int index3 = s3.length()-i-1;
        unsigned int num1 = index1>=0?mapping.at(s1[index1]):0;
        unsigned int num2 = index2>=0?mapping.at(s2[index2]):0;
        unsigned int result = index3>=0?mapping.at(s3[index3]):0;
        if(debug) std::cout<<num1<<" + "<<num2<<" + "<<carry<<" = "<<result<<" | ";
        if((num1+num2+carry)%10!=result){
            if(debug)std::cout<<"FALSE | DONE"<<std::endl;
            return false;
        }else{
            carry = (num1+num2+carry)/10;
            if(debug)std::cout<<"TRUE  | "<<"C: "<<carry<<std::endl;
        }
    }

    return true;
}





