#include "graaf.h"
#include "bellman-ford.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
	// initialiseer graaf
	GraafMetTakdata<GERICHT,int> graaf(9);
	
	// help var
	string line;
	stringstream ss;
	
	int from;
	int to;
	int weight;
	
	// open stream, read graph
	string file = "data.txt";
	ifstream reader(file.c_str());
	if(reader.is_open())
		while(getline(reader,line)){
			stringstream ss(line);
			ss >> from >> to >> weight;
			try{
				graaf.voegVerbindingToe(from,to,weight);
			}	
			catch(GraafExceptie ex){
				cout << ex;
			}
		}
	else
		cout << "failed to open " << file;
	
	BellmanFord bf(graaf);
	int start = 0;
	bf.calculateShortestPath(start);
	
	int out;
	cin >> out;
	return 0;
}