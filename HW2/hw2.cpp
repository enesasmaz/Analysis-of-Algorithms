/*
* kruskal.cpp
* 
* Created on: April 6th, 2021
*     Author: U�ur �nal
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

// Class to represent edges
class Edge {
	public:
		// Properties
		int source;
		int destination;
		int weight;
	public:
		// Constructor
		Edge(int source, int destination, int weight);
		
		// Getter methods for properties
		const int GetSource();
		const int GetDestination();
		const int GetWeight();
		
		// Operation overloading
		friend bool operator<(Edge const& leftHandSide, Edge const& rightHandSide);
		friend bool operator>(Edge const& leftHandSide, Edge const& rightHandSide);
		friend ostream& operator<<(ostream& os, Edge const& edge);
};

// Constructor only sets edge properties
Edge::Edge(int source, int destination, int weight) : source(source), destination(destination), weight(weight) { }

// Getter methods returns const value for security
const int Edge::GetSource() { return source; }
const int Edge::GetDestination() { return destination; }
const int Edge::GetWeight() { return weight; }

// To compare edges by their weight
bool operator<(Edge const& leftHandSide, Edge const& rightHandSide) {
    return leftHandSide.weight < rightHandSide.weight;
}
bool operator>(Edge const& leftHandSide, Edge const& rightHandSide) {
    return leftHandSide.weight > rightHandSide.weight;
}

// To print the edge properties
ostream& operator<<(ostream& os, Edge const& edge) {
	// Converts the numeric representation of a vertice back to a letter: (char) ('A' + value)
    os << (char) ('A' + edge.source) << " - " << (char) ('A' + edge.destination) << " : " << edge.weight;
    // Return value = "<source> - <destination> : <weight>"
    return os;
}

// Class to represent the graph, run the algorithms, contain and print the MSTs
class Graph {
	private:
		// Graph properties
		int numberOfVertices;
		vector<Edge> edges;
		
		// Edges in Minimum Spanning Tree for Kruskal's algorithm
		vector<Edge> kruskalMST;
	public:
		// Graph specific methods
		Graph(int numberOfVertices);
		void AddEdge(char source, char destination, int weight);
		void Print();
		
		// Kruskal's algorithm methods
		vector<int> CreateParents();
		int FindSet(vector<int> &parents, int vertice);
		void JoinSets(vector<int> &parents, int sourceParent, int destinationParent);
		void RunKruskal();
		void PrintKruskalMST();
};

// Constructor only sets the number of vertices
Graph::Graph(int numberOfVertices) : numberOfVertices(numberOfVertices) { }


// Adds an edge to the graph
void Graph::AddEdge(char source, char destination, int weight) {
	// Converts the letter of a vertice to a numeric representation: (source - 'A')
	edges.push_back(Edge(source - 'A', destination - 'A', weight));
}

// Prints the edges in the graph
void Graph::Print() {
	cout << "----------Graph----------" << endl;
	cout << "Edge  : Edge Weight" << endl;
	
	for (int i = 0; i < edges.size(); i++) {
		Edge edge = edges[i];
		
		// Prints the edge
		cout << edge << endl;
	}
}

// Creates a parent value of each vertice in the graph to calculate sets
vector<int> Graph::CreateParents() {
	vector<int> parents;
	
	for (int vertice = 0; vertice < numberOfVertices; vertice++) {
		// At first, each vertices are their own set so their parents are themselves.
		parents.push_back(vertice);
	}
	
	return parents;
}

// Returns the parent of the vertice to find its set
int Graph::FindSet(vector<int> &parents, int vertice) {
	int parent = parents[vertice];
	
	if (parent == vertice) { // If vertice is its own parent, returns the vertice
		return vertice;
	}
	else { // If vertice is not its own parent, returns its parent's parent
		return FindSet(parents, parent);
	}
}

// Joins sets by assigning both of their parents to the same parent
void Graph::JoinSets(vector<int> &parents, int sourceParent, int destinationParent) {
	parents[destinationParent] = parents[sourceParent];
}

// Creates Minimum Spanning Tree using Kruskal's Algorithm
void Graph::RunKruskal() {
	// Initilizes the parents of the vertices for set calculations
	vector<int> parents = CreateParents();
	// Just copied the edges of the graph not to modify original values
	// since we will use them for Prim's. This is not necessary for the algorithm.
	vector<Edge> graph = edges;
	
	// ALGORITHM STARTS
	
	// Sorts the edges by their weights in ascending order
	sort(graph.begin(), graph.end());
	
	int sourceParent, destinationParent;
	// Moves between edges from minumum weighted edge to maximum weighted one
	for (int i = 0; i < graph.size(); i++) {
		Edge edge = graph[i];
		
		// Finds the sets of the edge's source and destination by finding their parents
		sourceParent = FindSet(parents, edge.source);
		destinationParent = FindSet(parents, edge.destination);
		
		// If their sets are not the same
		if (sourceParent != destinationParent) {
			// Adds the edge to the Minimum Spanning Tree
			kruskalMST.push_back(edge);
			// Joins the two sets by combining their parents
			JoinSets(parents, sourceParent, destinationParent);
		}
	}
}

// Prints the edges in the Minimum Spanning Tree created by Kruskal's algorithm
// by addition order and the weight of the MST
void Graph::PrintKruskalMST() {
	// Initializes the weight of the MST to 0
	int weightOfMST = 0;
	
	cout << endl << "---Kruskal's Algorithm----" << endl;
	cout << "Edge  : Edge Weight" << endl;
	
	for (int i = 0; i < kruskalMST.size(); i++) {
		Edge edge = kruskalMST[i];
		
		// Prints the edge and adds the weight
		cout << edge << endl;
		weightOfMST += edge.weight;
	}
	cout << "Weight of the MST = " << weightOfMST << endl;
}

int main() {
	// Create the graph with the number of vertices that it will contain
	Graph graph(5);
	// Add all of the edges to the graph
	graph.AddEdge('C', 'A', 3);
	graph.AddEdge('C', 'D', 1);
	graph.AddEdge('C', 'B', 4);
	graph.AddEdge('A', 'B', 2);
	graph.AddEdge('B', 'D', 5);
	graph.AddEdge('B', 'E', 6);
	graph.AddEdge('D', 'E', 3);
	// Print all the edges in the graph
	graph.Print();
	
	// Run Kruskal's Algorithm and print the MST created by it
	graph.RunKruskal();
	graph.PrintKruskalMST();
	
	return 0;
}
