#include "proj1.hpp"
#include <iostream>
#include <map>
#include <string>
#include <set> 


bool puzzleSolver(std::string s1, std::string s2, std::string s3, std::map<char, unsigned> & mapping)
{
	if(s3.length()<s1.length() || s3.length()<s2.length()) return false;

	std::set<int> digits {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::set<char> letters;
	//add every character to set letters
	for(char const &c: s1+s2+s3){
		letters.insert(c);
	}
	//max of 10 vars
	if(letters.size()>10) return false;
	
	//case where **C+**Z =**C, we know Z = 0
	if(s1[s1.length()-1] == s3[s3.length()-1]){
		mapping.insert(std::pair<char,int>(s2[s2.length()-1],0));
		letters.erase(s2[s2.length()-1]);
		digits.erase(0);
	}
	//flip s1 and s2
	if(s2[s2.length()-1] == s3[s3.length()-1]){
		mapping.insert(std::pair<char,int>(s1[s1.length()-1],0));
		letters.erase(s1[s1.length()-1]);
		digits.erase(0);
	}
	//case A**+B** = C***, C = 1
	//if result is longer than both inputs, rightmost digit is 1
	if(s3.length()>s1.length() && s3.length()>s2.length()){
		mapping.insert(std::pair<char,int>(s3[0],1));
		letters.erase(s3[0]);
		digits.erase(1);
	}
	return puzzleSolverHelper(s1, s2, s3, mapping, digits, letters);
}


bool puzzleSolverHelper(	
					std::string s1,
					std::string s2,
					std::string s3,
					std::map<char, unsigned> & mapping,
					std::set<int> &digits,
					std::set<char> &letters)
{
	

	//no more letters
	
	if(letters.empty()){
		//check solution 
		return verifySolution(s1, s2, s3, mapping);
	}
	
	//pop a letter
	char c = *letters.begin();
	letters.erase(letters.begin());
	//loop through digits
	for (int d = 0; d<=9; d++){
		//check if we can still use d(if its still in digits)
		if(digits.find(d)!=digits.end()){
			//add c:d to map
			mapping.insert(std::pair<char,int>(c,d));
			//remove d from digits
			digits.erase(d);
			//try it out
			if(puzzleSolverHelper(s1, s2, s3, mapping, digits, letters)){
				//if it worked, return true
				return true;
			}
			//if it didnt work, remove that letter from map
			mapping.erase(c);
			digits.insert(d);
		}
		//loop: try another digit
	}
	//put letter back
	letters.insert(c);
	
	//nothing worked
	return false; 
}

void printMap(std::map<char, unsigned> & mapping, std::set<int> &digits, std::set<char> &letters){
	std::cout<<"digits: { ";
	for(auto elem: digits){
		std::cout<<elem<<" ";
	}
	std::cout<<"}\nletters: {";
	for(auto elem: letters){
		std::cout<<elem<<" ";
	}
	std::cout<<"}\nmapping: {"<<std::endl;
	for(auto elem : mapping){
   		std::cout <<"    "<< elem.first << ":" << elem.second << "\n";
	}
	std::cout<<"}\n"<<std::endl;

	
}

bool verifySolution(std::string s1, std::string s2, std::string s3, const std::map<char, unsigned> & mapping)
{
    bool debug = false;

    if(debug)std::cout<<"\n\n\n"<<s1<<" + "<<s2<<" = "<<s3<<"\n\n";
    if(s3.length()<s1.length() || s3.length()<s2.length()) return false;
	if(s3.length()>s1.length() && s3.length()>s2.length() && mapping.at(s3[0])!=1)return false;
    unsigned int carry  = 0;
    for(unsigned int i = 0; i<s3.length(); ++i){
        int index1 = s1.length()-i-1;
        int index2 = s2.length()-i-1;
        int index3 = s3.length()-i-1;
		
		unsigned num1 = index1>=0?mapping.at(s1[index1]):0;
		unsigned num2 = index2>=0?mapping.at(s2[index2]):0;
		unsigned result = index3>=0?mapping.at(s3[index3]):0;
        if(debug) std::cout<<num1<<" + "<<num2<<" + "<<carry<<" = "<<result<<" | ";
        if((num1+num2+carry)%10!=result){
            if(debug)std::cout<<"FALSE | DONE"<<std::endl;
            return false;
        }else{
            carry = (num1+num2+carry)/10;
            if(debug)std::cout<<"TRUE  | "<<"C: "<<carry<<std::endl;
        }
    }

    return carry == 0;
}
