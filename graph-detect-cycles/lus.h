#ifndef __lus__
#define __lus__
#include "graaf.h"
#include <vector>
#include <queue>
namespace lu{
	template <GraafType TYPE>
	class lus {
		public:
			lus(Graaf<TYPE>&);
			bool is_lus_ingraden();

		private:
			Graaf<TYPE> * g;
	};
	
	template <GraafType TYPE>
	lus<TYPE>::lus(Graaf<TYPE> & g){
		this->g = &g;
	}
	
	template <GraafType TYPE>
	bool lus<TYPE>::is_lus_ingraden(){
		bool is_lus = false;
		
		// calculate ingraden
		std::vector<int> ingraden(g->aantal_knopen(),0);
		for(int i = 0; i < g->aantal_knopen(); i++){
			Knoop verbindingen = g->knopen[i];
			Knoop::iterator it = verbindingen.begin();
			for(it; it != verbindingen.end(); it++)
				ingraden[it->first]+=1;
		}
		
		std::queue<int> next_ingraad;
		// push all ingraden=0 on the queue
		for(int i = 0; i < g->aantal_knopen();i++)
			if(ingraden[i]==0)
				next_ingraad.push(i);
		
		int count = 0;
		while(!next_ingraad.empty()){
			int current = next_ingraad.front();
			Knoop verbindingen = g->knopen[current];
			Knoop::iterator it = verbindingen.begin();
			for(it; it != verbindingen.end(); it++){
				ingraden[it->first]-=1;
				if(ingraden[it->first]==0)
					next_ingraad.push(it->first);
			}
			next_ingraad.pop();
			count++;
		}
		
		return (count==g->aantal_knopen())?false:true;
	}
	
}

#endif // __lus__