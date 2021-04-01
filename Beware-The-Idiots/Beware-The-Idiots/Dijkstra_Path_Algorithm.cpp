#include "Dijkstra_Path_Algorithm.h"

void Dijkstra_Path_Algorithm::read(Ovule) {   
	
    if (Ovule().numOfVert > 0) {
    	
        
        for (int i = 0;i < Ovule().numOfVert;i++) {
            cout << "Enter the (+ve)weights for the row " << i << endl;
            for (int j = 0;j < Ovule().numOfVert;j++) {
                cin >> adjMatrix[i][j];
                while (adjMatrix[i][j] < 0) {
                    cout << "Weights should be +ve. Enter the weight again\n";
                    cin >> adjMatrix[i][j];
                }
            }
        }
        cout << "Enter the source vertex\n";
        cin >> source;
        while ((source < 0) && (source > numOfVertices - 1)) {
            cout << "Source vertex should be between 0 and" << numOfVertices - 1 << endl;
            cout << "Enter the source vertex again\n";
            cin >> source;
        }
    }
}


void Dijkstra_Path_Algorithm::initialize() {
    for (int i = 0;i < numOfVertices;i++) {
        mark[i] = false;
        predecessor[i] = -1;
        distance[i] = INFINITY;
    }
    distance[source] = 0;
}


int Dijkstra_Path_Algorithm::getClosestUnmarkedNode() {
    int minDistance = INFINITY;
    int closestUnmarkedNode;
    for (int i = 0;i < numOfVertices;i++) {
        if ((!mark[i]) && (minDistance >= distance[i])) {
            minDistance = distance[i];
            closestUnmarkedNode = i;
        }
    }
    return closestUnmarkedNode;
}


void Dijkstra_Path_Algorithm::calculateDistance() {
    initialize();
    int minDistance = INFINITY;
    int closestUnmarkedNode;
    int count = 0;
    while (count < numOfVertices) {
        closestUnmarkedNode = getClosestUnmarkedNode();
        mark[closestUnmarkedNode] = true;
        for (int i = 0;i < numOfVertices;i++) {
            if ((!mark[i]) && (adjMatrix[closestUnmarkedNode][i] > 0)) {
                if (distance[i] > distance[closestUnmarkedNode] + adjMatrix[closestUnmarkedNode][i]) {
                    distance[i] = distance[closestUnmarkedNode] + adjMatrix[closestUnmarkedNode][i];
                    predecessor[i] = closestUnmarkedNode;
                }
            }
        }
        count++;
    }
}


void Dijkstra_Path_Algorithm::printPath(int node) {
    if (node == source)
        cout << (char)(node + 97) << "..";
    else if (predecessor[node] == -1)
        cout << "No path from “<<source<<”to " << (char)(node + 97) << endl;
    else {
        printPath(predecessor[node]);
        cout << (char)(node + 97) << "..";
    }
}


void Dijkstra_Path_Algorithm::output() {
    for (int i = 0;i < numOfVertices;i++) {
        if (i == source)
            cout << (char)(source + 97) << ".." << source;
        else
            printPath(i);
        cout << "->" << distance[i] << endl;
    }
}