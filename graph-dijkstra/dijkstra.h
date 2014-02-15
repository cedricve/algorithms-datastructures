// // // // // // // // // // //
//
//
//  Dijkstra's algorithm by
//	www.cedricve.me
//
//
// // // // // // // // // // //

#ifndef __DIJKSTRA__
#define __DIJKSTRA
#include "ggraaf.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// connection (struct)
// to keep from node, to node and the cost between
// 1 object, this will make everything easier
struct connection {
	int from;
	int to;
	double cost;
	connection(int f,int t,int c){
		from = f;
		to = t;
		cost = c;
	}
	// we need to overload this method because
	// we will use a priority queue that will contain
	// connection objects
	bool operator<(const connection & c) const{
		// we want a min priority queue (or heap)
		// that's why we say false
		// if 15 > 18 => return true;
		if(c.cost>cost)
			return false;
		else 
			return true;
	}
};

template<typename T>
class Dijkstra{
	private:
		// Starting node
		int start;
		// TRUE if we looped a node his neighbors
		// if v[5] == true => means we discovered (node 5) all his neighbors
		vector<bool> connected;
		// Represents the cost to every node from
		// the starting node
		vector<double> costs;
		// priority queue to get the connection with
		// the lowest cost
		priority_queue<connection> pq;
	public:
		Dijkstra(GewogenGraaf<ONGERICHT,T> &):start(0){}
		Dijkstra(GewogenGraaf<ONGERICHT,T> &,int);
		void discover_neighbors(GewogenGraaf<ONGERICHT,T> &,int);
	
};

template<typename T>
Dijkstra<T>::Dijkstra(GewogenGraaf<ONGERICHT,T> &g,int s){
	start = s;
	// initialize both vectors, with the amount of nodes
	// that the graph contains
	connected.resize(g.aantal_knopen());
	costs.resize(g.aantal_knopen());
	
	// Increase costs to MAX
	for(unsigned int i = 0; i < costs.size(); i++)
		costs[i] = 99999999;
	// All connected are false
	for(unsigned int i = 0; i < connected.size();i++)
		connected[i] = false;
	
	// The cost to himself is zero (0) => DUUh!
	costs[s]=0;

	discover_neighbors(g,s);
	
	while(!pq.empty())
	{
		connection c = pq.top();
		// if this neighbor isn't connected
		// get all his neighbors
		if(!connected[c.to])
			discover_neighbors(g,c.to);
		pq.pop();
	}
	
	for(unsigned int i = 0; i < costs.size(); i++)
	{
		cout << "From ("<< s <<") To ("<< i <<"): " << costs[i] << endl;
	}
}

template<typename T>
void Dijkstra<T>::discover_neighbors(GewogenGraaf<ONGERICHT,T> &g,int node_id){
	// we discovered this node
	connected[node_id]=true;
	
	// get the current cost of this node
	// look in the costs vector
	double current_cost = costs[node_id];
	
	// Get all neighbors from this node
	// we can call the [] operator from the graph class
	// this methode will return all connections from this node
	// This will be stored in an object Knoop => this is just a map<int,int> object
	// The map contains the neighbor_id and the connection_id (connection_id we will need to get the cost from a specific connection)
	Knoop connections = g[node_id];
	// we will loop this map or Knoop object with an iterator
	
	int cost_neighbor;
	int total_cost;
	int neighbor;
	for(Knoop::iterator itr = connections.begin(); itr != connections.end();itr++){
		// get the neighbor id from the map
		neighbor = itr->first;
		// check if this neighbor is allready connected
		if(!connected[neighbor])
		{
			// get the cost from the current node to this neighbor
			cost_neighbor = g.gewicht(itr->second);
			// sum the current cost and the cost of the neighbor
			total_cost = current_cost + cost_neighbor;
			// check is this cost is smaller than the original cost in the costs vector
			// if so change his cost and push it on the priority queue
			if(total_cost<costs[neighbor])
			{
				connection c(node_id,neighbor,total_cost);
				pq.push(c);
				// change the NEW (lower) cost
				costs[neighbor]=total_cost;
			}
		
		}
	}
}
#endif
