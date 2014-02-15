#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cmath>
#include <vector>
#include "csv.h"
#include "splaytree.h"
#include "generator.h"
using namespace std;

int dataPoints=6000;

int main(int argc, char *argv[]){
	CsvData graph("depth",',');
    Generator pointGenerator;
	SplayTree<double,unsigned int> thetree;
    vector<double> depth;
    int count=0;
	
    for (int i=0; i<dataPoints; i++ ){
        double point=pointGenerator.getPoint();
		thetree.voegtoe(point,i);
        count++;
        if (count*50 >= dataPoints){
            depth.push_back(thetree.depth());
            count=0;
        }
    }

    graph.addData(depth);
	cout << "finished";
	cout<< thetree;
	
    return 0;
}
