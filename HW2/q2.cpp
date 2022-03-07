/*
QUESTION 2
ENES ŞAŞMAZ 150170090
I could not finish this question, but I was thinking a lot about it.
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
#include <limits.h>
#include <stdio.h>

using namespace std;

int minDistance(int dist[], bool sptSet[], int V)
{
	int min = INT_MAX, min_index;
	for (int v = 0; v < V; v++){
		if (sptSet[v] == false && dist[v] <= min){
	        min = dist[v], min_index = v;
        }
    }
	return min_index;
}

void dijkstra(vector<vector<int>> graph, int src, int V)
{
	int *dist = new int(V);

	bool *sptSet = new bool(V);

	for (int i = 0; i < V; i++){ 
		dist[i] = INT_MAX, sptSet[i] = false;
    }

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++) {

		int u = minDistance(dist, sptSet, V);

		sptSet[u] = true;
		for (int v = 0; v < V; v++){
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]){
				dist[v] = dist[u] + graph[u][v];
            }
        }
	}
}

int main()
{
	string file;
	cin >> file;
	ifstream path_info;
	set<string> vertices;
    map<string, int> represent;
	string line, fsource, fdestination, fweight;
	int intweight;


	path_info.open(file);
	while (!path_info.eof())
	{
		getline(path_info, fsource, ',');
		getline(path_info, fdestination, ',');
		getline(path_info, fweight, '\n');
		vertices.insert(fsource);
		vertices.insert(fdestination);
	}
	path_info.close();

    vector<vector<int>> vect(vertices.size() , vector<int> (vertices.size(), 0));
    
    set<string>::iterator it = vertices.begin();
    for(unsigned int i = 0; i < vertices.size(); i++){
        represent.insert(pair<string, int>(*it, i));
        it++;
    }

    path_info.open(file);
	while (!path_info.eof())
	{
		getline(path_info, fsource, ',');
		getline(path_info, fdestination, ',');
		getline(path_info, fweight, '\n');
		intweight = stoi(fweight);
        vect[represent.find(fsource)->second][represent.find(fdestination)->second] = intweight;
    }

	dijkstra(vect, represent.find("Ma")->second, vertices.size());


	return 0;
}
