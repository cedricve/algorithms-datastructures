#ifndef __LONGESTPATH_H
#define __LONGESTPATH_H

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
using namespace std;
 
/*
	Longest Path Graph Algorithm
	by cedricve.me
	- 	Calculate the longest path of a graph
*/
 
class LongestPath {
	public:
		LongestPath(const GraafMetTakdata<GERICHT,int> & graaf):graph(graaf){};
		int getLongestPath();
		void calculateLongestPath(const int &, int &);
		// Helper functions
		int numberOfNodes();
		int getWeight(const int &, const int &);
	protected:
		GraafMetTakdata<GERICHT,int> graph;
};
 
int LongestPath::getLongestPath(){
	int longest_path = 0;
	int number_of_nodes = numberOfNodes();
	int i = 0;
 
	while(i<number_of_nodes && longest_path < number_of_nodes+1)
			calculateLongestPath(i++,longest_path);
 
	if(longest_path == number_of_nodes+1)
		return 99999999;
	else	
		return longest_path;
}
 
void LongestPath::calculateLongestPath(const int & start, int & longest_path){
	//initialize
	int number_of_nodes = numberOfNodes();
	queue<int> lookForBetter;
	vector<int> weights(number_of_nodes,0);
	weights[start] = 0;
	lookForBetter.push(start);
 
	//Start looking for longer :)
	while(!lookForBetter.empty() && longest_path < number_of_nodes+1){
		// Get Next from Queue
		int look = lookForBetter.front();
 
		// Get current cost (hops)
		int current_cost = weights[look];
 
		// Get connections from look
		map<int,int> connections = graph[look];
		for(map<int,int>::iterator it = connections.begin(); it != connections.end(); it++){
			if(weights[it->first]<current_cost+getWeight(look,it->first)){
 
				// Yes this is a longer path ...
				weights[it->first]=current_cost+getWeight(look,it->first);
				lookForBetter.push(it->first);
 
				// Look if this path is longer than the current max
				if(longest_path<weights[it->first])
					longest_path = weights[it->first];
 
			}
		}		
		// Remove from queue
		lookForBetter.pop();
	}
 
}
 
int LongestPath::getWeight(const int & from, const int & to){
	return *graph.geefTakdata(from,to);
}
 
int LongestPath::numberOfNodes(){
	return graph.aantalKnopen();
}
 
 
#endif // __LONGESTPATH_H