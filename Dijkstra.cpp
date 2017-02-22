#include "Graph.h"
#include <iostream>
using namespace std;

int readTotalFileLines(char * file);
void computeDijkstra(char* argv[]);
void computeAstar(char* argv[]);
void computeID(char* argv[]);
void printOutput(vector<Nodes*> a, int firstNode, int lastNode);
int main(int argc, char* argv[]) {
	if (argc == 5 || argc == 6) {
		string a = argv[1];
		if (a == "dijkstra" && argc == 5) {
			computeDijkstra(argv);
		}
		else if (a == "Astar" && argc == 6) {
			computeAstar(argv);
		}
		else if (a == "ID") {
			computeID(argv);
		}
		else {
			cout << "enter a valid distance algorithm" << endl;
		}
	}
	else {
		cout << "enter valid arguements" << endl;
	}
	return 0;
}


int readTotalFileLines(char * file) {
	fstream inputFile(file, ios_base::in);
	int lineCount = -1;
	int nodeNum;
	float temp;
	while(inputFile >> nodeNum) {
		inputFile >> nodeNum;
		if (nodeNum > lineCount)
			lineCount = nodeNum;

		inputFile >> nodeNum;
		if (nodeNum > lineCount)
			lineCount = nodeNum;

		inputFile >> temp;
	}

	return lineCount;

}
void computeDijkstra(char* argv[]) {
	int totalCoordinates = readTotalFileLines(argv[2]);
	
	if(totalCoordinates < 2) {
		printf("not enough locations\n");
		return;
	}
	Graph hello;
	vector<Nodes*> weightedGraph = hello.createGraph(argv[2], totalCoordinates);
	for (int x = 0; x < weightedGraph.size(); x++) {
		if (weightedGraph[x] == nullptr) {
			cout << "bad input file" << endl;
			return;
		}
	}
	/*for (int i = 0; i < weightedGraph.size(); i++) {
		cout << "Node: " << weightedGraph[i]->id;
		for (int j = 0; j < weightedGraph[i]->friends.size(); j++) {
			cout << "  distance " << weightedGraph[i]->friends[j]->distance;	
		}
		cout << endl;
	}*/
	int first = stoi(argv[3]);
	int last = stoi(argv[4]);
	if (first - last == 0) {
		cout << "not enough points" << endl;
		return;
	}
	if (first < 0 || first > totalCoordinates || last < 0 || last > totalCoordinates) {
		cout << "points out of bounds" << endl;
		return;
	}
	vector<Nodes*> computedShortestDistance = hello.calcShortestDijkstra(weightedGraph, first, last);
	//print result
	
	printOutput(computedShortestDistance, first, last);
	
	for (int i = 0; i < totalCoordinates + 1; i++) {
		int j = weightedGraph[i]->friends.size();
		for (int x = 0; x < j; x++) {
			delete weightedGraph[i]->friends[x];		
		}
		delete weightedGraph[i];
	}

}
void computeAstar(char* argv[]) {
	int totalCoordinates = readTotalFileLines(argv[2]);
	
	if(totalCoordinates < 2) {
		printf("not enough locations\n");
		return;
	}
	Graph hello;
	vector<Nodes*> weightedGraph = hello.createGraph(argv[2], totalCoordinates);
	for (int x = 0; x < weightedGraph.size(); x++) {
		if (weightedGraph[x] == nullptr) {
			cout << "bad input file" << endl;
			return;
		}
	}

	vector<Coordinate*> coordinateSystem = hello.createCoordinates(argv[3], totalCoordinates);
	/*for (int i = 0; i < coordinateSystem.size(); i++) {
		cout << "Node: " << coordinateSystem[i]->id;
		cout << "x: " << coordinateSystem[i]->xCoord << "  y:" << coordinateSystem[i]->yCoord;
		cout << endl;
	}*/

	int first = stoi(argv[4]);
	int last = stoi(argv[5]);
	if (first - last == 0) {
		cout << "not enough points" << endl;
		return;
	}

	if (first < 0 || first > totalCoordinates || last < 0 || last > totalCoordinates) {
		cout << "points out of bounds" << endl;
		return;
	}

	vector<Nodes*> computedShortestDistance = hello.calcShortestAStar(weightedGraph, coordinateSystem, first, last);
	//print result
	printOutput(computedShortestDistance, first, last);
	for (int i =0; i < totalCoordinates + 1; i++) {
		int j = weightedGraph[i]->friends.size();
		for (int x = 0; x < j; x++) {
			delete weightedGraph[i]->friends[x];		
		}
		delete weightedGraph[i];
		weightedGraph[i] = NULL;
	}
	int fs = coordinateSystem.size();
	for (int j = 0; j < fs; j++) {
		delete coordinateSystem[j];
		coordinateSystem[j] = NULL;
	}
	
	
}

void computeID(char* argv[]) {


}

void printOutput(vector<Nodes*> computedShortD, int first, int last) {
	//if dijkstra 
	Nodes* sd = computedShortD[last];
	//else if dijkstra
	Nodes* sd2 = sd->closestDistance;
		
	cout << sd->distanceFromStart << endl;
	vector<int> fin;
	bool route = true;
	while(sd != nullptr) {
		int id = sd2->id;
		for (int i = 0; i < sd->friends.size(); i++) {
			if (sd->friends[i]->id == id) {
				fin.push_back(sd->friends[i]->edgeID);
				break;
			}
		}
		if (sd2->id == first) {
			break;
		}
		else if (sd2->closestDistance == nullptr) {
			cout << "inf" << endl;
			route = false;
			break;
		}
		else {
			sd = sd->closestDistance;
			sd2 = sd->closestDistance;
		}

	}
	if (route) {
		int count = 0;
		for (int i = (fin.size() - 1); i >= 0; i--) {
			cout << fin[i] << endl;
		}
	}
	sd = NULL;
	sd2 = NULL;
	/*
	vector<int> finale;
	while(sd != nullptr) {
		int id = sd2->id;
		for(int i = 0; i < sd->friends.size(); i++) {
			if (sd->friends[i]->id == id) {
				finale.push_back(sd->friends[i]->edgeID);
				break;
			}
		}
		if (sd2->closestDistance == nullptr) {
			break;
		}
		else {
			sd = sd->closestDistance;
			sd2 = sd->closestDistance;
		}
	}
	
	for (int i = finale.size() - 1; i >= 0; i--) {
		cout << i << ":  " << finale[i] << endl;
	}*/

}

