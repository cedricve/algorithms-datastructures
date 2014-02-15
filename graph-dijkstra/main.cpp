#include <iostream>
#include "dijkstra.h"
#include <fstream>

using namespace std;
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
	
	Dijkstra<int> d(g,2);
	
    return 0;
}
