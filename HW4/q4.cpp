/* * * * * * * * * * * * * * * * * * * * * * * * * *
 * BLG 336E Analysis of Algorithms II
 * Spring 2021
 * Student Name: ENES ŞAŞMAZ
 * Student ID: 150170090
 * * * * * * * * * * * * * * * * * * * * * * * * * */
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

using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int> >& graph) {
        // Y O U R   C O D E   H E R E
        // Vector to store colour of vertex assiging all to -1 i.e. uncoloured colours are either 0 or 1.
        vector<int> color(graph.size(), -1);
        // Queue for BFS storing.
        queue<pair<int, int>> q;
        // Loop incase graph is not connected.
        for (size_t i = 0; i < graph.size(); i++)
        {
            if (color[i] == -1)
            {
                // Colouring with 0.
                q.push({i, 0});
                color[i] = 0;
                while (!q.empty())
                {
                    pair<int ,int> p = q.front();
                    q.pop();
                    int vertex = p.first;
                    int colour = p.second;
                    // If already coloured with parent vertex color then bipartite graph is not possible.
                    for (size_t j : graph[vertex])
                    {
                        if (color[j] == colour)
                        {
                            return false;
                        }
                        if (color[j] == -1)
                        {
                            if (colour)
                            {
                                color[j] = 0;
                            }
                            else
                            {
                                color[j] = 1;
                            }
                            q.push({j, color[j]});
                        }   
                    }              
                }
            }
        }
        // If all vertexes are coloured such that no two connected vertex have same colours.
        return true;
    }
};

// This function is provided to check if your graph data is stored well or not
void printv(vector <vector <int> > v) {
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = 0; j < v[i].size(); j++)
            cout << v[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    // Solution class for bipartite-ness problem
    Solution s;

    // Read data filename from std input stream and open it with file handler/pointer
    string fname;
    cin >> fname;
    ifstream graphFileHandler(fname);

    // An array of integers to store neighbours of a vertex
    vector <int> adj;
    // A 2D array of integers to store neighbours of each vertex in a graph
    vector<vector <int> > graph;

    string line;
    // Read from the file until there is no new line left
    while (graphFileHandler >> line) {
        // Save line as string stream object
        stringstream ss(line);
        // Get a string variable
        string substr;

        // Until the end of the line, read the line as substings separated by commas
        while (ss.good()) {
            getline(ss, substr, ',');
            // Push the substring in adjacency list, we got a neighbour here
            adj.push_back(stoi(substr));
        }

        // When line ends, push all the neighbours of the vertex into the graph
        graph.push_back(adj);

        // Clear the array, before the next iteration begins
        // Next iteration, we will read the subsequent line from the file and it will contain neighbours of some other guy
        adj.clear();
    }

    // Check if data file is read in the way it is supposed to be
    // D O   N O T   P R I N T   T H E   G R A P H   I N   Y O U R   S O L U T I O N
    // The expected output only includes a True or a False not the graph data itself
    // Do not uncomment this line
    // printv(graph);

    // Save the return value of the function
    bool answer = s.isBipartite(graph);

    // If answer is True, print True otherwise False
    if (answer == 1)
        cout << "True" <<endl;
    else
        cout << "False" << endl;

    return 0;
}
