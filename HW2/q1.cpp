/*
QUESTION 1
ENES ŞAŞMAZ 150170090
*/

#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<cstring>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<algorithm>

using namespace std;

class Edge {	
	public:
		string source;
		string destination;
		int weight;
		Edge(string source, string destination, int weight);
		const string GetSource();
		const string GetDestination();
		const int GetWeight();
		friend bool operator<(Edge const& leftHandSide, Edge const& rightHandSide);
		friend bool operator>(Edge const& leftHandSide, Edge const& rightHandSide);
		friend ostream& operator<<(ostream& os, Edge const& edge);
};

Edge::Edge(string source, string destination, int weight) : source(source), destination(destination), weight(weight) { }

const string Edge::GetSource() { return source; }
const string Edge::GetDestination() { return destination; }
const int Edge::GetWeight() { return weight; }

bool operator<(Edge const& leftHandSide, Edge const& rightHandSide) {
    return leftHandSide.weight < rightHandSide.weight;
}
bool operator>(Edge const& leftHandSide, Edge const& rightHandSide) {
    return leftHandSide.weight > rightHandSide.weight;
}

class Graph {
	public:
		int numberOfVertices;
		vector<Edge> edges;
		vector<Edge> kruskalMST;
		map<string, int> represent;
		Graph(int numberOfVertices);
		void AddEdge(string source, string destination, int weight);
		vector<int> CreateParents();
		int FindSet(vector<int> &parents, int vertice);
		void JoinSets(vector<int> &parents, int sourceParent, int destinationParent);
		void RunKruskal();
};

Graph::Graph(int numberOfVertices) : numberOfVertices(numberOfVertices) { }

void Graph::AddEdge(string source, string destination, int weight) {
	edges.push_back(Edge(source, destination, weight));
}

vector<int> Graph::CreateParents() {
	vector<int> parents;
	for (int vertice = 0; vertice < numberOfVertices; vertice++) {
		parents.push_back(vertice);
	}
	return parents;
}

int Graph::FindSet(vector<int> &parents, int vertice) {
	int parent = parents[vertice];
	if (parent == vertice) { 
		return vertice;
	}
	else { 
		return FindSet(parents, parent);
	}
}

void Graph::JoinSets(vector<int> &parents, int sourceParent, int destinationParent) {
	parents[destinationParent] = parents[sourceParent];
}

void Graph::RunKruskal() {
	vector<int> parents = CreateParents();
	vector<Edge> graph = edges;
	sort(graph.begin(), graph.end());
	
	int sourceParent, destinationParent;

	for (unsigned int i = 0; i < graph.size(); i++) {
		Edge edge1 = graph[i];
		if (edge1.source == "GP" && edge1.destination.at(0) == 'C')
		{
			sourceParent = FindSet(parents, represent.find(edge1.source)->second);
			destinationParent = FindSet(parents, represent.find(edge1.destination)->second);
			if (sourceParent != destinationParent) {
				kruskalMST.push_back(edge1);
				JoinSets(parents, sourceParent, destinationParent);
			}
			break;
		}
	}	
	for (unsigned int i = 0; i < graph.size(); i++) {
		Edge edge2 = graph[i];
		if (edge2.source == "GP" && edge2.destination.at(1) == 'i')
		{
			sourceParent = FindSet(parents, represent.find(edge2.source)->second);
			destinationParent = FindSet(parents, represent.find(edge2.destination)->second);
			if (sourceParent != destinationParent) {
				kruskalMST.push_back(edge2);
				JoinSets(parents, sourceParent, destinationParent);
			}
			break;
		}
	}	
	for (unsigned int i = 0; i < graph.size(); i++) {
		Edge edge = graph[i];
		if (edge.source.at(1) == 'p' && edge.destination.at(1) == 'p') {
			continue;
		}
		if (edge.source == "Hipp" && edge.destination.at(0)== 'B') {
			continue;
		}
		else {
			sourceParent = FindSet(parents, represent.find(edge.source)->second);
			destinationParent = FindSet(parents, represent.find(edge.destination)->second);
			if (sourceParent != destinationParent) {
				kruskalMST.push_back(edge);
				JoinSets(parents, sourceParent, destinationParent);
			}
		}
	}
}


int main() {
	
	string file;
	cin >> file;
	ifstream city_plan;
	set<string> vertices;
	string line, fsource, fdestination, fweight;
	int intweight;
	int result = 0;

	city_plan.open(file);
	while (!city_plan.eof())
	{
		getline(city_plan, fsource, ',');
		getline(city_plan, fdestination, ',');
		getline(city_plan, fweight, '\n');
		vertices.insert(fsource);
	   	vertices.insert(fdestination);
	}
	city_plan.close();

	Graph graph(vertices.size());

	city_plan.open(file);
	while (!city_plan.eof())
	{
		getline(city_plan, fsource, ',');
		getline(city_plan, fdestination, ',');
		getline(city_plan, fweight, '\n');
		intweight = stoi(fweight);
		graph.AddEdge(fsource, fdestination, intweight);
	}
	
	set<string>::iterator it = vertices.begin();
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		graph.represent.insert(pair<string, int>(*it, i));
		it++;
	}
	
	
	graph.RunKruskal();

	sort(graph.kruskalMST.begin(), graph.kruskalMST.end());
    for (auto it = graph.kruskalMST.begin(); it != graph.kruskalMST.end(); ++it){
        cout <<it->source  << " " << it->destination << " " << it->weight << endl;
        result = result + it->weight;
    }

    cout << result << endl;

	
	return 0;
}
