#ifndef __BELLMANFORT_H
#define __BELLMANFORT_H

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
using namespace std;

/*
	Bellman Ford Algorithm
	by cedricve.me
	- 	Calculate the shortest path on a directed graph
		with negative or positive weights, if you know
		the weights will be positive in advance you better
		use Dijkstra as it's more efficient.
	-	This algorithm won't work if there are negative cycles
		this will cause an infinite loop
*/

class BellmanFord {
	public:
		BellmanFord(const GraafMetTakdata<GERICHT,int> & graaf):bf_graaf(graaf){};
		void calculateShortestPath(const int &);
		void print(const int &, const vector<int> &);
		// Helper functions
		int numberOfNodes();
		int getWeight(const int &, const int &);
	protected:
		GraafMetTakdata<GERICHT,int> bf_graaf;
};

void BellmanFord::calculateShortestPath(const int & start){
	//initialize
	int number_of_nodes = numberOfNodes();
	queue<int> lookForBetter;
	vector<int> weights(number_of_nodes,99);
	weights[start] = 0;
	lookForBetter.push(start);
	
	//Start looking for better :)
	while(!lookForBetter.empty()){
		// Get Next from Deque
		int look = lookForBetter.front();
		
		// Get current cost
		int current_cost = weights[look];
		
		// Get connections from look
		map<int,int> connections = bf_graaf[look];
		for(map<int,int>::iterator it = connections.begin(); it != connections.end(); it++){
			if(weights[it->first]>current_cost+getWeight(look,it->first)){
				// Yes this is a better path ...
				weights[it->first]=current_cost+getWeight(look,it->first);
				lookForBetter.push(it->first);
			}
		}		
		// Remove from deque
		lookForBetter.pop();
	}
	
	// print result
	print(start,weights);

}

int BellmanFord::getWeight(const int & from, const int & to){
	return *bf_graaf.geefTakdata(from,to);
}

int BellmanFord::numberOfNodes(){
	return bf_graaf.aantalKnopen();
}

void BellmanFord::print(const int & start, const vector<int> & weights){
	cout << "Shortest path from " << start << " to .." << endl;
	for(int i = 0; i < numberOfNodes(); i++)
		cout << "Node " << i << ": " << weights[i] << ", ";
}


#endif // __BELLMANFORT
