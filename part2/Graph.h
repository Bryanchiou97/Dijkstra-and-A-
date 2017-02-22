#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;

typedef struct friendNodes{
	float distance;
	int id;
	int edgeID;
	friendNodes(int id, float distance, int edgeID) {
		this->id = id;
		this->distance = distance;
		this->edgeID = edgeID;
		
	}
}friendNodes;


typedef struct Nodes{
	int id;
	double distanceFromStart;
	double estDistance;
	int inQueue;
	Nodes* closestDistance;
	vector<friendNodes*> friends;
	Nodes(int id) {
		this->id = id;
		this->distanceFromStart = -1;
		closestDistance = nullptr;
		inQueue = 0;
	}

}Nodes;

typedef struct Coordinate{
	int id;
	double xCoord;
	double yCoord;
	Coordinate(int id, double xCoord, double yCoord) {
		this->id = id;
		this->xCoord = xCoord;
		this->yCoord = yCoord;
	}
}Coordinate;

struct compare
{
	bool operator()(Nodes* a, Nodes* b) {
		if (a->id > b->id)
			return true;
		else
			return false;
	}
};

struct compareScore
{
	bool operator()(Nodes* a, Nodes* b) {
		if(a->estDistance > b->estDistance) 
			return true;
		else 
			return false;
	}
};


class Graph{

	public: 
		//insert methods here
		vector<Nodes*> createGraph(char * filename, int coordinates);
		vector<Coordinate*> createCoordinates(char * filename, int coordinates);
		//void createGraph(char * filename, int coordinates);
		vector<Nodes*> calcShortestDijkstra(vector<Nodes*> createdGraph, int startingPoint, int endingPoint);
		vector<Nodes*> calcShortestAStar(vector<Nodes*> createdGraph, vector<Coordinate*> points, int startingPoint, int endingPoint);
		double straightDistance(vector<Coordinate*> coordVec, int startingPoint, int endingPoint); 
};
