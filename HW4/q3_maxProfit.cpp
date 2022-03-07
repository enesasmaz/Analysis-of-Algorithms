/*
* q3_maxProfit_skeleton.cpp
*
* Created on: June 14th, 2021
*     Author: U�ur �nal
*/
/***********************************************************
STUDENT INFORMATION
Full Name : Enes Şaşmaz
Student ID: 150170090
**********************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, set<int>> MaxProfit(int numOfCrystals, vector<int> profits, vector<int> entryCosts)
{
	/****************************************************************/
	/********* YOU NEED TO USE HERE AS BASE OF YOUR METHOD! *********/
	/* YOU CAN USE HELPER METHODS BUT main() WILL CALL THIS METHOD! */
	/****************************************************************/

	int numOfCities = profits.size(); // It could also be entryCost.size() .
	int** matrix = new int*[numOfCities+1]; //It is used to define 2D dynamic array.
	for (int i = 0; i < numOfCities+1; i++)
	{
		matrix[i] = new int[numOfCrystals+1];
	}
	for (int i = 0; i < numOfCities+1; i++) // It is used to initialize the 2D matrix with zeros.
	{
		for (int j = 0; j < numOfCrystals+1; j++)
		{
			matrix[i][j] = 0;
		}
	}
	for (unsigned int i = 1; i < profits.size()+1; i++)
	{
		for (int j = 1; j < numOfCrystals+1; j++)
		{
			if (entryCosts[i-1] > j)
			{
				matrix[i][j] = matrix[i-1][j];
			}
			else
			{
				matrix[i][j] = max(matrix[i-1][j], profits[i-1] + matrix[i-1][j-entryCosts[i-1]]);
			}				
		}	
	}
	int maxProfit = matrix[numOfCities][numOfCrystals];
	int k = numOfCities;
	int l = numOfCrystals;
	set<int> citiesToVisit;
	while (k && l > 0)
	{
		if (matrix[k][l] != matrix[k-1][l])
		{
			citiesToVisit.insert(k);
			l = l - entryCosts[k-1];
		}
		k = k - 1;
	}
	
	cout << "Dynaming Programming Table" << endl;
	for (int i = 0; i <= numOfCities; i++) {
		for (int j = 0; j <= numOfCrystals; j++) {
			cout << std::right << std::setw(3) << matrix[i][j];
		}
		cout << endl;
	}

	return pair<int, set<int>>(maxProfit, citiesToVisit);
}

int main() {
	int numOfCrystals;
	vector<int> profits;
	vector<int> entryCosts;
	
	string inputFilename;
	cout << "Enter the name of the input file: ";
	cin >> inputFilename;

	ifstream input(inputFilename);

	if (!input.is_open()) {
		cerr << "File named \"" << inputFilename << "\" could not open!" << endl;
		return EXIT_FAILURE;
	}

	string line;
	if (getline(input, line)) {
		numOfCrystals = stoi(line);
	}
	while (getline(input, line, ' ')) {
		profits.push_back(stoi(line));
		getline(input, line);
		entryCosts.push_back(stoi(line));
	}

	pair<int, set<int>> result = MaxProfit(numOfCrystals, profits, entryCosts);

	cout << "Max profit is " << result.first << "." << endl;
	cout << "Cities visited:";
	for (int cityNumber : result.second) {
		cout << " " << cityNumber;
	}
	cout << endl;
}

