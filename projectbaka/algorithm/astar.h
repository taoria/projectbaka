#include <vector>
namespace astar {
	struct Node {
		int data;
		int x;
		int y;
	};
	class AStar {
	private:
		int sizeX;
		int sizeY;
		std::vector<Node*>  matrix;
	public:
		AStar(int maX,int maY);
	};
}
