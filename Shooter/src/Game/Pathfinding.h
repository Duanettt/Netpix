#pragma once
#include <vector>
#include "../Scene/Scene.h"

#define GRID_CELL_SIZE 15

struct Node
{
	bool isWalkable;
	int x;
	int y;

	int hCost;
	int gCost;

	int fCost() { return hCost + gCost; }
	friend std::ostream& operator<<(std::ostream& out, const Node& n);
};

class Pathfinding
{
public:

	Pathfinding();
	Pathfinding(Foreground fg);

	void findPath(Node* startNode, Node* targetNode);

	int Heuristic(Node* startNode, Node* targetNode);

	Node* getNodeAt(int x, int y);

	void createGrid();

	int worldToGridY(float worldY);

	std::pair<int, int> worldToGrid(float worldX, float worldY);

	std::pair<float, float> gridToWorld(int gridX, int gridY);


	std::vector<Node*> getNeighbours(Node* node);

	void DrawGrid();

private:
	std::vector<Node> grid;
	int worldWidth;
	int worldHeight;
	int minY;
	int maxY;
};

