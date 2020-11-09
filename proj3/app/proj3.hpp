#ifndef ___PROJECT_3_HPP
#define ___PROJECT_3_HPP

#include <string>
#include <map>
#include <set>
#include "Wordset.hpp"

void loadWordsIntoTable(WordSet & words, std::istream & in);


std::string convert(std::string s1, std::string s2, const WordSet & words);
std::string getPath(std::map<std::string, std::string> paths, std::string s1, std::string s2);



#endif
