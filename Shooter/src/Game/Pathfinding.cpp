#include "Pathfinding.h"

Pathfinding::Pathfinding() : minY(190), maxY(275)
{
	Foreground fg(std::string("b2_4"));

	this->worldHeight = fg.getHeight();
	this->worldWidth = fg.getWidth() * 2;

	createGrid();
}

Pathfinding::Pathfinding(Foreground fg)
{
	this->worldHeight = fg.getHeight();
	this->worldWidth = fg.getWidth() * 2;
}

Node* Pathfinding::getNodeAt(int x, int y)
{

	// Perform checks to ensure x is not out of bounds or anything silly.
	if (x <= 0 || x >= worldWidth || y <= 0 || y >= worldHeight) return nullptr;

	// Index row major order formula to convert this 2D array to 1D

	// Y * worldWidth gives us the total number of cell before we reach Y we then add x to get the exact value since thats the offset.
	int index = y * worldWidth + x;

	//std::cout << grid[index] << std::endl;
	return &grid[index];
}


void Pathfinding::findPath(Node* startNode , Node* targetNode)
{
	// Learn DSA to sharpen knowledge on the A* Algorithm
	std::priority_queue<Node*> openList;

}

int Pathfinding::Heuristic(Node* startNode, Node* targetNode)
{
	int dx = abs(startNode->x - targetNode->x);
	int dy = abs(startNode->y - targetNode->y);

	return (dx + dy);
}

void Pathfinding::createGrid()
{
	grid.clear();
	grid.reserve(worldHeight * worldWidth);

	for (int y = 0; y < worldHeight; y++)
		for (int x = 0; x < worldWidth; x++)
		{

			Node node;

			node.x = x;
			node.y = y;
			//node.y = y;
			grid.push_back(node);

		}

}

int Pathfinding::worldToGridY(float worldY)
{
	if (worldY < minY) worldY = minY;
	if (worldY > maxY) worldY = maxY;

	int gridY = static_cast<int>((worldY - minY) / (maxY - minY) * (worldHeight - 1));
	return gridY;
}

// Utility functions pretty much, didnt really get this but will provide an explanation later.
std::pair<int, int> Pathfinding::worldToGrid(float worldX, float worldY) {
	int gridX = static_cast<int>(worldX);
	int gridY = static_cast<int>((worldY - minY) / (maxY - minY) * (worldHeight - 1));
	return { gridX, gridY };
}

std::pair<float, float> Pathfinding::gridToWorld(int gridX, int gridY) {
	float worldX = static_cast<float>(gridX);
	float worldY = minY + (static_cast<float>(gridY) / (worldHeight - 1)) * (maxY - minY);
	return { worldX, worldY };
}


std::vector<Node*> Pathfinding::getNeighbours(Node* node)
{

	std::vector<Node*> neighbours;

	const int directions[4][2] = {
		{ 0 , 1}, {0, -1}, 
		{ 1, 0}, {-1, 0}
	};

	for (const auto& direction : directions)
	{
		int neighbourX = node->x + direction[0];
		int neighbourY = node->y + direction[1];

		Node* neighbourNode = getNodeAt(neighbourX, neighbourY);


		neighbours.push_back(neighbourNode);
	}

	return neighbours;

}

void Pathfinding::DrawGrid() {
	for (int y = 0; y < worldHeight; ++y) {
		for (int x = 0; x < worldWidth; ++x) {
			// Drawing lines instead of rectangles to avoid performance hit
			DrawLine(x * GRID_CELL_SIZE, y * GRID_CELL_SIZE,
				(x + 1) * GRID_CELL_SIZE, y * GRID_CELL_SIZE, LIGHTGRAY);
			DrawLine(x * GRID_CELL_SIZE, y * GRID_CELL_SIZE,
				x * GRID_CELL_SIZE, (y + 1) * GRID_CELL_SIZE, LIGHTGRAY);
		}
	}
}




std::ostream& operator<<(std::ostream& out, const Node& n)
{
	out << "Node.x:  " << n.x << " Node.y: " << n.y;

	return out;
}
