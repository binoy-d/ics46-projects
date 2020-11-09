#include "proj3.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}


// You probably want to change this function.
std::string convert(std::string s1, std::string s2, const WordSet & words)
{
	
	if(!words.contains(s1)){
		return "impossible";
	}
	std::queue<std::string> todo;
	std::set<std::string> used;
	todo.push(s1);
	int wordSize = s1.size();

	std::map<std::string, std::string> paths;

	while(!todo.empty()){
		int origSize = todo.size();
		
		
		
		for(int j = 0; j<origSize; ++j){
			std::string current = todo.front();
			todo.pop();
			for(int i = 0; i<wordSize; ++i){
				std::string preserved = current;
				char prevChar = current[i];//preserve char
				for(char c = 'a'; c<='z'; ++c){
					current[i] = c;
					//if we reached, trace back
					if(current == s2){
						paths.insert(std::pair<std::string, std::string>(current, preserved));
						return getPath(paths, s1, s2);
					}	
					//if its a valid word, and hasnt been used yet
					if(used.find(current)==used.end() && words.contains(current)){
						used.insert(current);//use it, and add to queue
						todo.push(current);
						paths.insert(std::pair<std::string, std::string>(current, preserved));
					}
				}
				current[i] = prevChar;//reset that word
			}
		}

		
	}

	return "foo";  // stub obviously 
}


std::string getPath(std::map<std::string, std::string> paths, std::string s1, std::string s2){
	std::string current = s2;
	std::stack<std::string> st;
	while(current!=s1){
		st.push(current);
		current = paths[current];
	}
	st.push(current);
	std::string out = "";
	while(!st.empty()){
		out+=" --> ";
		out+=st.top();
		st.pop();
		
	}


	return out.substr(5);
}

