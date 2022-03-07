/***********************************************************
2021 Spring - BLG 336E-Analysis of Algorithms II
Final Project
Question on Greedy Algorithms
Modified Dijkstra Algorithms for Maximum Capacity Path
Submitted: 15.06.2021 
**********************************************************/

/***********************************************************
STUDENT INFORMATION
Full Name : Enes Şaşmaz
Student ID: 150170090
**********************************************************/

// Some of the libraries you may need have already been included.
// If you need additional libraries, feel free to add them
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector> 
#include <stdlib.h>
#include <time.h>  
#include <fstream>
#include <string>
#include <chrono> 
#include <iterator>
#include <map>
#include <queue>
#include <utility>
// Do not change this definition
#define INT_MAX 1000


using namespace std;

class Graph{
public:
	int node_count;
	int edge_count;
	int** adjacency_matrix;

	Graph(){};
	void read_file(char* filename);
	void print_adjacency_matrix(); // in case you need
	int weight(int i, int j){return this->adjacency_matrix[i][j];}
	~Graph();
};

Graph::~Graph(){
	for(int i = 0; i < node_count; i++){
		delete [] adjacency_matrix[i];
	}
}

void Graph::print_adjacency_matrix(){	
	// Prints the adjacency matrix
	for(int i = 0; i < node_count; i++){
		for(int j = 0; j < node_count; j++){
			cout<<adjacency_matrix[i][j]<<", ";
		}
		cout<<endl;
	}
}

void Graph::read_file(char* filename){
	
	/*********************************************/
	/****** CODE HERE TO READ THE TEXT FILE ******/
	/*********************************************/
	
	int s, d, w, first;
	int count = 0;
	ifstream file(filename);
	file >> first;
	node_count = first;
	adjacency_matrix = new int*[node_count];
	for(int i = 0; i < node_count; ++i) {
    	adjacency_matrix[i] = new int[node_count];
	}
	for(int i = 0; i < node_count; i++){
		for(int j = 0; j < node_count; j++){
			adjacency_matrix[i][j] = -1;
		}
	}
	while (!file.eof())
	{
		file >> s;
		file >> d;
		file >> w;
		adjacency_matrix[s][d] = w;
		adjacency_matrix[d][s] = w;
		count++;
	}
	edge_count = count;
}

void Modified_Dijkstra(Graph* graph){

	/*********************************************/
	/****** CODE HERE TO FOR THE ALGORITHM *******/
	/*********************************************/
	int* status = new int[graph->node_count];
	int* wt = new int[graph->node_count];
	int* dad = new int[graph->node_count];
	int count = 0;
	for (int i = 0; i < graph->node_count; i++)
	{
		status[i] = 0;
		wt[i] = -1;
		dad[i] = -1;
	}
	status[0] = 2;
	wt[0] = INT_MAX;
	for (int i = 0; i < graph->node_count; i++)
	{
		if (graph->weight(0,i) != -1)
		{
			status[i] = 1;
			wt[i] = graph->weight(0,i);
			dad[i] = 0;
		}
	}
	for (int i = 0; i < graph->node_count; i++)
	{
		if (status[i] == 1)
		{
			count++;
		}
	}
	while (count)
	{
		int v = 0;
		int max = 0;
		for (int i = 0; i < graph->node_count; i++)
		{
			if (status[i] == 1)
			{
				if (wt[i] > max)
				{
					max = wt[i];
					v = i;
				}
			}
		}
		status[v] = 2;
		for (int i = 0; i < graph->node_count; i++)
		{
			if (graph->weight(v,i) != -1)
			{
				if (status[i] == 0)
				{
					status[i] = 1;
					count++;
					wt[i] = min(wt[v], graph->weight(v,i));
					dad[i] = v;
				}
				else if (status[i] == 1 && wt[i] < min(wt[v], graph->weight(v,i)))
				{
					wt[i] = min(wt[v],graph->weight(v,i));
					dad[i] = v;
				}
			}	
		}
		count--;
	}

	/*********************************************/
	/***** DO NOT CHANGE THE FOLLOWING LINES *****/
	/**** THEY PRINT OUT THE EXPECTED RESULTS ****/
	/*********************************************/
	
	// The following line prints wt array (or vector).
	// Do not change anything in the following lines.
	cout<<"###########RESULTS###########"<<endl;
	cout<<endl;
	
	cout<<"1. WT ARRAY"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"  ";
	for(int i = 0; i < graph->node_count - 1; i++){
		cout << wt[i] << ", ";
	}
	cout << wt[graph->node_count - 1] << endl;
	
	// The following lines print the final path.
	// Do not change anything in the following lines.
	int iterator = graph->node_count - 1;
	vector<int> path_info;
	path_info.push_back(iterator);
	while(iterator != 0){
		path_info.push_back(dad[iterator]);
		iterator = dad[iterator];
	}
	cout<<endl;
	cout<<"2. MAXIMUM CAPACITY PATH"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"  ";
	vector<int>::iterator it;
    for (it = path_info.end() - 1; it > path_info.begin(); it--)
        cout << *it << " -> ";
    cout<<*path_info.begin()<<endl;
    
    cout<<endl;
    cout<<"3. MAXIMUM CAPACITY"<<endl;
    cout<<"------------------------"<<endl;
    cout<<"  ";
    cout<<wt[graph->node_count - 1]<<endl;
    cout<<"#############################"<<endl;
    
    return;
}

int main(int argc, char **argv){
	Graph* graph = new Graph();
	graph->read_file(argv[1]);
	Modified_Dijkstra(graph);
	return 0;	
}
