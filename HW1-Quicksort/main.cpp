#include<iostream>
#include<fstream>
#include<string>
#include <chrono>

using namespace std;

typedef struct Sales
{
	string country;
	string type;
	string id;
	int units;
	float profit;
}Sales;

void swap(Sales& a, Sales& b) 
{ 
   	struct Sales t;
	t = a;
	a = b;
	b = t;
}

int operation (Sales* x, int low, int high) 
{ 
    string pivot = x[high].country;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) 
    { 
        if (x[j].country <= pivot) 
        { 
			if (x[j].country == pivot)
			{
				if (x[j].profit > x[high].profit)
				{
            		i++;
					swap(x[i], x[j]);
				}
			}
			else if (x[j].country < pivot)
			{
				i++;
				swap(x[i], x[j]);
			}
        } 
    } 
    swap(x[i + 1], x[high]); 

    return (i + 1); 
} 

void quickSort(Sales* y, int low, int high) 
{ 
    if (low < high) 
    {
        int op = operation(y, low, high); 

        quickSort(y, low, op - 1); 
        quickSort(y, op + 1, high); 
    } 
} 

int main(int argc, char *argv[]){
	
	ifstream file;
	file.open("sales.txt");
	if (!file){
		cerr << "File cannot be opened!";
		exit(1);
	}
	
	char* num = argv[1];
    int N = atoi(num);
	

	Sales* theSales;
	theSales = new Sales[N];	

	string line,
		   header,
		   country,
		   type,
		   id;			
	int units;
	float profit;
	
	getline(file, header); //this is the header line
	
	for(int i = 0; i<N; i++){
		getline(file, country, '\t'); //country (string)
		theSales[i].country = country;
		getline(file, type, '\t'); //item type (string)
		theSales[i].type = type;
		getline(file, id, '\t'); //order id (string)
		theSales[i].id = id;
		file >> units; //units sold (integer)
		theSales[i].units = units;
		file >> profit; //total profit (float)
		theSales[i].profit = profit;
	    getline(file, line, '\n'); //this is for reading the \n character into dummy variable.
	}

	auto start = chrono::high_resolution_clock::now();
	quickSort(theSales, 0, (N-1));
	auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Elapsed time: " << elapsed.count() << " s\n";
	
	ofstream file_new;
    file_new.open("sorted.txt");
	
	file_new << header << endl;
	
	for (int i = 0; i < N; i++)
	{
		file_new << theSales[i].country << "\t";
		file_new << theSales[i].type << "\t";
		file_new << theSales[i].id << "\t";
		file_new << theSales[i].units << "\t";
		file_new << theSales[i].profit << "\t" << endl;
	}

	return 0;
}