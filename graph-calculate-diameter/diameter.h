#include "graaf.h"
#include <queue>
#include <vector>

template <GraafType TYPE>
class diameter {
	public:
		diameter(Graaf<TYPE>&);
		int getDiameter_BFS();
		int getDiameter_DIJKSTRA();
	private:
		Graaf<TYPE> * g;
};

template <GraafType TYPE>
diameter<TYPE>::diameter(Graaf<TYPE> & g){
	this->g = &g;
}

template <GraafType TYPE>
int diameter<TYPE>::getDiameter_BFS(){
	// get number of vertices
	int aantal = g->aantal_knopen();
	int diameter = 0;
	// calculate shortest hops for every vertex to another vertex
	for(int i = 0; i < aantal; i++)
	{
		int current_largest = 0;
		std::queue<int> que;
		que.push(i);
	
		std::vector<bool> bezet(aantal,false);
		std::vector<int> afstand(aantal,999);
		afstand[i] = 0;

		// BFS
		while(!que.empty()){
			int current = que.front();
			bezet[current] = true;
			Knoop verbindingen = g->knopen[current];
			Knoop::iterator it = verbindingen.begin();
			for(it; it != verbindingen.end(); it++)
				if(!bezet[it->first]){
					que.push(it->first);
					afstand[it->first] = afstand[current] + 1;
					if(afstand[it->first]>current_largest)
						current_largest = afstand[it->first];
				}
			que.pop();
		}
		// if longest hops is bigger than current diameter
		if(diameter < current_largest)
			diameter = current_largest;
	}
	return diameter;
}

struct Vertex{
	int id;
	int weight;
	Vertex(int id):id(id),weight(1){};
	friend bool operator< (Vertex v, Vertex v2){
		// nasty solution!
		return v.weight > v2.weight;
	}
};

template <GraafType TYPE>
int diameter<TYPE>::getDiameter_DIJKSTRA(){
	// get number of vertices
	int aantal = g->aantal_knopen();
	int diameter = 0;
	
	// calculate shortest hops for every vertex to another vertex
	for(int i = 0; i < aantal; i++)
	{
		std::vector<bool> bezet(aantal,false);
		std::vector<int> afstand(aantal,999);
		afstand[i] = 0;
		
		std::priority_queue<Vertex> pque;
		int current_largest = 0;
		Vertex v(i);
		pque.push(v);
		
		while(!pque.empty()){
			Vertex v = pque.top();
			bezet[v.id] = true;
			Knoop verbindingen = g->knopen[v.id];
			Knoop::iterator it = verbindingen.begin();
			
			int current_distance = afstand[v.id];
			for(it; it != verbindingen.end(); it++)
				if(!bezet[it->first]){
					if(afstand[it->first]>current_distance+v.weight){
						pque.push(it->first);
						afstand[it->first] = current_distance+v.weight;
						if(afstand[it->first]>current_largest)
							current_largest = afstand[it->first];
					}
				}
				
			pque.pop();
		}
		
		// if longest hops is bigger than current diameter
		if(diameter < current_largest)
			diameter = current_largest;
	}
	return diameter;
}
