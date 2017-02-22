#include "Graph.h"
#include <queue>

vector<Nodes*> 
Graph::createGraph(char * filename, int coordinates) {
	//if out of bounds, then its a bad input
	vector<Nodes*> weightedGraph(coordinates + 1);
	fstream inputFile(filename, ios_base::in);
	int param1;
	int firstNode;
	int secondNode;
	float distance;
	while(inputFile >> param1) {
		inputFile >> firstNode;
		inputFile >> secondNode;
		inputFile >> distance;
		if (weightedGraph[firstNode] == NULL) 
			weightedGraph[firstNode] = new Nodes(firstNode);
		if (weightedGraph[secondNode] == NULL) 
			weightedGraph[secondNode] = new Nodes(secondNode);

		weightedGraph[firstNode]->friends.push_back(new friendNodes(secondNode, distance, param1));
		weightedGraph[secondNode]->friends.push_back(new friendNodes(firstNode, distance, param1));
	}
	inputFile.close();
	return weightedGraph;
}

vector<Coordinate*> 
Graph::createCoordinates(char * filename, int coordinates) {
	vector<Coordinate*> data(coordinates + 1);
	fstream inputFile(filename, ios_base::in);
	int nodeID;
	double xAxis;
	double yAxis;
	while(inputFile >> nodeID) {
		inputFile >> xAxis;
		inputFile >> yAxis;
		data[nodeID] = new Coordinate(nodeID, xAxis, yAxis);
	}
	return data;
}
vector<Nodes*>
Graph::calcShortestDijkstra(vector<Nodes*> createdGraph, int startingPoint, int endingPoint) {
	int graphSize = createdGraph.size();
	//vector<Nodes*> unvisted;
	vector<Nodes*> visited(graphSize);
	
	//priority_queue<Nodes*, vector<Nodes*>, compare> mypq;
	queue<Nodes> mypq;
	
	Nodes a = *createdGraph[startingPoint];
	createdGraph[startingPoint]->distanceFromStart = 0;
	a.distanceFromStart = 0;
	mypq.push(a);
	//calculation time
	while(1) {
		if (mypq.empty()) {
			break;
		}
		//take front of queue and calc distance
		Nodes temp = mypq.front();
		mypq.pop();
		//check all neighbors
		double nodeDistance = temp.distanceFromStart;
		for(int j = 0; j < temp.friends.size(); j++) {
			int neighbor = temp.friends[j]->id;
			if (visited[neighbor] == nullptr) {
				double edgeDistance = temp.friends[j]->distance;
				double computedDistance = nodeDistance + edgeDistance; 
				double currentDistance = createdGraph[neighbor]->distanceFromStart;
				if (currentDistance == -1 || computedDistance < currentDistance) {
					//update the distance
					createdGraph[neighbor]->distanceFromStart = computedDistance;
					createdGraph[neighbor]->closestDistance = createdGraph[temp.id];
					// check ^^
				}
				if (createdGraph[neighbor]->inQueue == 0) { 
					createdGraph[neighbor]->inQueue = 1;
					mypq.push(*createdGraph[neighbor]);
				}
			}
			
		}
		visited[temp.id] = createdGraph[temp.id];
	}
	return visited;

}

vector<Nodes*>
Graph::calcShortestAStar(vector<Nodes*> createdGraph, vector<Coordinate*> points, int startingPoint, int endingPoint) {
	int graphSize = createdGraph.size();
	vector<Nodes*> visited(graphSize);
	
	priority_queue<Nodes*, vector<Nodes*>, compareScore> mypq;
	Nodes* a = createdGraph[startingPoint];
	a->distanceFromStart = 0;
	mypq.push(a);
	//test pquee sorting 
	/*for (int i = 0; i < createdGraph.size(); i++) {
	
		mypq.push(createdGraph[i]);
	}

	while (!mypq.empty()) {
		Nodes* a = mypq.top();
		mypq.pop();
		cout << "id: " << a->id << endl;
	}*/
	//calculation time
	int breakstatement = false;
	while(1) {
		if (mypq.empty() || breakstatement) {
			break;
		}
		//take front of queue and calc distance
		Nodes * temp = mypq.top();
		mypq.pop();
		//check all neighbors
		double nodeDistance = temp->distanceFromStart;
		for(int j = 0; j < temp->friends.size(); j++) {
			int neighbor = temp->friends[j]->id;
			if (visited[neighbor] == nullptr) {
				double edgeDistance = temp->friends[j]->distance;
				double computedDistance = nodeDistance + edgeDistance; 
				double currentDistance = createdGraph[neighbor]->distanceFromStart;
				if (currentDistance == -1 || computedDistance < currentDistance) {
					//update the distance
					createdGraph[neighbor]->distanceFromStart = computedDistance;
					double sss = straightDistance(points, neighbor, endingPoint) + computedDistance;	
					createdGraph[neighbor]->estDistance = sss;
					//node chain to keep track
					createdGraph[neighbor]->closestDistance = temp;
					// check ^^
				}
				if (createdGraph[neighbor]->inQueue == 0) { 
					createdGraph[neighbor]->inQueue = 1;
					mypq.push(createdGraph[neighbor]);
				}
			}
			if (temp->id == endingPoint) {
				breakstatement = true;
				break;
			}
		}
		visited[temp->id] = temp;
	}
	return visited;

}

double
Graph::straightDistance(vector<Coordinate*> data, int startingPoint, int endingPoint) {
	//find magnitude of slope
	double x1 = data[startingPoint]->xCoord; 
	double y1 = data[startingPoint]->yCoord;
	double x2 = data[endingPoint]->xCoord;
	double y2 = data[endingPoint]->yCoord;
	double x = pow((x2-x1), 2);
	double y = pow((y2-y1), 2);
	double sour = sqrt(x+y);
	return sour;

}











