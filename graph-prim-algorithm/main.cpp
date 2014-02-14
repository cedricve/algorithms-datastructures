// // /// // // // // /// // // // // /// // //
//											 //
//		prim algorithm by cedricve.me		 //
//											 //
// // /// // // // // /// // // // // /// // //

#include "ggraaf.h"
#include <fstream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

// KnoopRelation is a class that represent a single connection
// knoop_from = the connection starts
// knoop_to = the connection ends
// weight = the weight of the connection
//
// the operator < needs to be overloaded because we will create
// objects of this class which will be added to a priority_queue
// so the priority_queue needs to know on which values he need
// to differentiate them from each other. 
struct KnoopRelation {
	int knoop_from;
	int knoop_to;
	int weight;
	KnoopRelation(int k, int l, int g) : knoop_from(k), knoop_to(l), weight(g) {};

	bool operator<(const KnoopRelation& knoopje) const {
        return weight>knoopje.weight;   
    }
};

// The prim class just calculates the minimal spanning tree
// thats all...
template <GraafType TYPE,typename T>
class Prim {
	public:
		void setGraph(GewogenGraaf<TYPE, T> g);
		void minimalSpanningTree();
		bool contains(int k);
	protected:
		GewogenGraaf<TYPE, T> graph;
		priority_queue<KnoopRelation> priorqueue;
		vector<int> pad;
		vector<bool> discovered;
};


// Contains(int node)
// check if a connection is not between 2 nodes that are already in the pad.
// so only connections to nodes which aren't allready in the pad vector.
template <GraafType TYPE,typename T>
bool Prim<TYPE,T>::contains(int k){
	for(unsigned int i=0; i < pad.size();i++)
		if(k == pad[i])
			return true;
	return false;
}

// calculates minimal spanning tree with prim's algorithm
template <GraafType TYPE,typename T>
void Prim<TYPE,T>::minimalSpanningTree()
{
	
	cout << "Running prim's legendary algorithm:" << endl;
	// sum of weights to calculate the total weight
	int weight = 0;
	
	// number of nodes
	unsigned int countnodes = graph.aantal_knopen();
	
	// initialize discovered
	discovered.reserve(countnodes);
	pad.reserve(countnodes);
	for(unsigned int i = 0; i < countnodes; i++)
		discovered[i] = false;
		
	// we start in 0 so this one is discovered
	int starting_point = 0;
	pad.push_back(starting_point);
	discovered[starting_point] = true;
		
	// loop for each node of the graph (so all nodes will contain the minimal spanning tree)
	// we need to add n-1 other nodes
	for(unsigned int i = 1; i < countnodes; i++)
	{
		
		// Get the connections
		// from our starting point
		map<int, int> connections = graph[starting_point];
		for(map<int, int>::iterator itr = connections.begin(); itr != connections.end(); ++itr){
			// check if a connection to a new node
			if(!discovered[itr->first])
			{
				// create a new object and push it to the priority queue
				KnoopRelation rknoop(starting_point,(*itr).first,graph.gewicht((*itr).second));
				priorqueue.push(rknoop);
			}
		}

		// we cancel all bad nodes (which are already in our MOB)
		while(pad.size()!=countnodes && discovered[priorqueue.top().knoop_to])
			priorqueue.pop();
		
		// we discovered our new node that we will add
		// to our MOB
		discovered[priorqueue.top().knoop_to] = true;
		
		// get the minimal pad from the priority queue
		pad.push_back(priorqueue.top().knoop_to);
		
		// add new weight to total weight
		weight += priorqueue.top().weight;
		
		// prints out the minimal destination , from --- (weight)--> to
		cout << priorqueue.top().knoop_from << "---- (weight:"<< 
			priorqueue.top().weight <<") ---->" << 
			priorqueue.top().knoop_to << endl;
		
		// Our new starting_point
		starting_point = priorqueue.top().knoop_to;
		
	}
	
	cout << "Total weight: " << weight << endl;
	
}

// sets graph in the prim class
template <GraafType TYPE,typename T>
void Prim<TYPE,T>::setGraph(GewogenGraaf<TYPE, T> g)
{
	graph = g;
}


int main() {
	
	GewogenGraaf<ONGERICHT, int> g;
	
	ifstream fileReader;
	string file = "graaf.txt";
	fileReader.open(file.c_str());
	
	// check if file exists (try opening it)
	if(!fileReader.is_open()){
		cout << "Can't open: " << file << endl;
		return 1;
	}
	
	// pass file to lees method of class ggraph.ccp
	// this method reads out the file and creates a graph structure
	try {
		g.lees(fileReader);
	} catch (GraafExceptie ge) {
		cout << ge << endl;
		return 1;
	}
	
	// create prim object and runs prim's algorithm on the weighted graph object
	Prim<ONGERICHT, int> primalgoritme;
	primalgoritme.setGraph(g);
	primalgoritme.minimalSpanningTree();
	 
	int end;
	cin >> end;
	return 0;	
}
