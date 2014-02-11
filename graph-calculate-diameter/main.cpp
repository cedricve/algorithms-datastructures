#include "diameter.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(){
	Graaf<GERICHT> ggraaf;
	ifstream reader("graph.txt");
	if(reader.is_open()){
		try {
			ggraaf.lees(reader);
		} catch (GraafExceptie ge) {
			cout << ge << endl;
			return 1;
		}
	}
	else
		return 1;
	
	diameter<GERICHT> diam(ggraaf);
	// Get Diameter with BFS
	cout << diam.getDiameter_BFS() << endl;
	// Get Diameter with Dijkstra
	cout << diam.getDiameter_DIJKSTRA();
	
	return 0;
}