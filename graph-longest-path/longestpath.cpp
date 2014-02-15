#include "graaf.h"
#include "longestpath.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
 
int main(){
	// initialize graph
	GraafMetTakdata<GERICHT,int> graaf(9);
 
	// help var
	string line;
	stringstream ss;
 
	int from;
	int to;
 
	// open stream, read graph
	string file = "data.txt";
	ifstream reader(file.c_str());
	if(reader.is_open())
		while(getline(reader,line)){
			stringstream ss(line);
			ss >> from >> to;
			try{
				graaf.voegVerbindingToe(from,to,1);
			}	
			catch(GraafExceptie ex){
				cout << ex;
			}
		}
	else
		cout << "failed to open " << file;
 
	LongestPath lp(graaf);
	cout << lp.getLongestPath();
 
	int out;
	cin >> out;
	return 0;
}