// ENES ŞAŞMAZ
// 150170090
// HOMEWORK-2
// Analysis of Algorithms I - CRN - 15175

#include <iostream>
#include <cmath>
#include <vector> 
#include <stdlib.h>
#include <time.h>  
#include <fstream>
#include <string>
#include <chrono>
using namespace std; 

vector<double> taxis;

ifstream file;
double distance(double longitude, double latitude)
{
    return sqrt(pow((33.40819-longitude), 2) + pow((39.19001-latitude), 2));
}

int parent(int i) 
{ 
	return (i - 1) / 2; 
} 

int left(int i) 
{ 
	return ((2 * i) + 1); 
} 

int right(int i) 
{ 
	return ((2 * i) + 2); 
} 

void swap(int& a, int& b){

    int temp;
    temp = a;
    a = b;
    b = temp;
}

void moveUp(int i) 
{ 
	while (i > 0 && taxis[parent(i)] > taxis[i]) { 
		swap(taxis[parent(i)], taxis[i]); 
		i = parent(i); 
	} 
} 

void moveDown(int i) 
{ 
	int maxIndex = i; 
	int l = left(i); 
	if (l <= (taxis.size() - 1) && taxis[l] < taxis[maxIndex]) { 
		maxIndex = l; 
	} 
	int r = right(i); 
	if (r <= (taxis.size() - 1) && taxis[r] < taxis[maxIndex]) { 
		maxIndex = r; 
	} 
	if (i != maxIndex) { 
		swap(taxis[i], taxis[maxIndex]); 
		moveDown(maxIndex); 
	} 
} 

void add_taxi(double p) 
{ 
	taxis.push_back(p); 
	moveUp((taxis.size() - 1)); 
}

void update_taxi(int i) 
{ 
    taxis[i] = taxis[i] - 0.01; 
    moveUp(i); 
} 

double call_taxi() 
{ 
	double get_taxi = taxis[0];
	taxis[0] = taxis[(taxis.size() - 1)];
	taxis.pop_back();
	moveDown(0);
	return get_taxi;
} 

void add_or_update(int p, int& add, int& update)
{

	double a, b;
	for (int i = 0; i < 100; i++)
	{
		int random_index = rand() % 10;
		if (taxis.size() != 0 && p > random_index)
		{
			int random_number = rand() % (taxis.size());
			update_taxi(random_number);
			update++;
		}
		else if (p <= random_index)
		{            
			file >> a;
			file >> b;
			double taxi_distance = distance(a,b);
			add_taxi(taxi_distance);
			add++;
		}
	}
}

int main(int argc, char *argv[]) 
{ 
	srand (time(NULL));

	file.open("locations.txt");
	if (!file){
		cerr << "File cannot be opened!";
		exit(1);
	}
	
	char* num = argv[1];
	int m = atoi(num);
	char* num2 = argv[2];
	float p = atof(num2);	
	p = p*10;
	
	string header;
	getline(file, header); //this is the header line
	
	int add_number = 0, update_number = 0;
	
	auto start = chrono::high_resolution_clock::now();
	
	cout << "Called taxis:" << endl;
	for(int i = 0; i < (m/100); i++){
		add_or_update(p , add_number, update_number);
		double distance_called_taxi = call_taxi();
		cout << distance_called_taxi << endl;
	}
	
	auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;

	cout << "The number of taxi additions:" << add_number << endl;
	cout << "The number of taxi updates:" << update_number << endl;

	cout << "Elapsed time: " << elapsed.count() * 1000 << " ms\n";

	return 0; 
} 