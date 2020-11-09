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
	std::queue<std::string> todo;
	WordSet used;
	todo.push(s1);
	int wordSize = s1.size();

	std::map<std::string, std::string> paths;
	// basically BFS except you need 2 for loops 
	// to get adjacencent nodes(words that are off by 1 letter)
	while(!todo.empty()){
		std::string current = todo.front();
		todo.pop();
		for(int i = 0; i<wordSize; ++i){
			std::string prev = current;//preserve word
			for(char c = 'a'; c<='z'; ++c){
				current[i] = c;
				//if we reached, trace back
				if(current == s2){
					paths.insert(std::pair<std::string, std::string>(current, prev));
					return getPath(paths, s1, s2);
				}	
				//if its a valid word, and hasnt been used yet
				if(!used.contains(current) && words.contains(current)){
					used.insert(current);//use it, and add to queue
					todo.push(current);
					paths.insert(std::pair<std::string, std::string>(current, prev));
				}
			}
			current = prev;//reset that word
		}	
	}
	return "if you're seeing this i have failed miserably, please have mercy on me";  // stub obviously 
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

