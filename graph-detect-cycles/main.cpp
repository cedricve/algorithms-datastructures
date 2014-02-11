#include "lus.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace lu;

int main(){
	Graaf<GERICHT> ggraaf;
	ifstream reader("graph1.txt");
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
	
	lus<GERICHT> ls(ggraaf);
	cout << ls.is_lus_ingraden();
	
	return 0;
}