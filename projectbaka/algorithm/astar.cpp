#include "astar.h"
astar::AStar::AStar(const int maX,const int maY){
	for (int i = 0; i < maX; i++) {
		matrix.push_back(new Node);
	}
}
