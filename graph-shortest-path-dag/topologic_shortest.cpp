#include "ggraaf.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;


void neighbors(int start,const GewogenGraaf<GERICHT,int> & g, vector<int> & distances){
	map<int,int> connections = g[start];
	int weight = distances[start];
	
	for(map<int,int>::iterator itr = connections.begin(); itr!=connections.end();itr++)
	{
		int new_weight = weight + g.gewicht(itr->second);
		if(distances[itr->first]>new_weight)
		{
			distances[itr->first]=new_weight;
			neighbors(itr->first,g,distances);
		}
	}
}

vector<int> get_shortest_path(int start,const GewogenGraaf<GERICHT,int> & g){
	
	vector<int> distances(g.aantal_knopen());
	for(unsigned int i = 0; i < distances.size(); i++)
		distances[i] = numeric_limits<int>::max();
	
	// we start in our starting point so
	distances[start] = 0;
	neighbors(start,g,distances);
	return distances;
}



int main(){
	
	string file = "acyclicgraph.txt";
	ifstream fileReader;
	fileReader.open(file.c_str());
	
	if(!fileReader.is_open())
	{
		cout << "File can't open!";
		return 1;
	}
	
	GewogenGraaf<GERICHT,int> g;
	g.lees(fileReader);
	
	int start = 0;
	vector<int> distances = get_shortest_path(start,g);
	
	for(unsigned int i = 0; i < distances.size(); i++)
		cout << start << " =("<< distances[i] <<")=> " << i << endl;
		
	
	return 0;
}