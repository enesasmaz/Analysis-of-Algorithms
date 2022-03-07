/*
HOMEWORK 3
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
#include <climits>

using namespace std;
ofstream output("output.txt");

class Cell
{
public:
    vector<string> inputarray;
    int left, up, diagonal;
    int value;
    int match = 1;
    int mis_match = -1;
    int gap = -5;
    int max_value(Cell temp)
    {
        int comp [4] = {temp.left, temp.up, temp.diagonal, 0};
        int* cmp_tmp = max_element(comp,comp+4);
        return cmp_tmp[0];
    };
    void fill_zero(Cell** arr, int x, int y)
    {
        int rows = inputarray[x].size() + 1;
        int cols = inputarray[y].size() + 1;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                arr[i][j].value = 0;
            }
        }
    };
    void fill_matrix(Cell** arr, int x, int y)
    {
        int rows = inputarray[x].size() + 1;
        int cols = inputarray[y].size() + 1;
        for (int i = 1; i < rows; i++)
        {
            for (int j = 1; j < cols; j++)
            {
                if (inputarray[x][i-1]==inputarray[y][j-1])
                {
                    arr[i][j].diagonal = arr[i-1][j-1].value + match;
                }
                else
                {
                    arr[i][j].diagonal = arr[i-1][j-1].value + mis_match;
                }
                arr[i][j].left = arr[i-1][j].value + gap;
                arr[i][j].up = arr[i][j-1].value + gap;
                arr[i][j].value = max_value(arr[i][j]);
            }
        }        
    };
    void traceback_and_print(Cell** arr, int x, int y)
    {   
        int count = 0;
        int maxElement = INT_MIN;
        string sequence;
        string seqs[20];
        int rows = inputarray[x].size() + 1;
        int cols = inputarray[y].size() + 1;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (arr[i][j].value > maxElement) 
                {
                    maxElement = arr[i][j].value;
                }
            }
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (arr[i][j].value == maxElement) 
                {
                    for (int k = 0; k < maxElement; k++)
                    {
                        sequence = sequence + inputarray[x][i-(maxElement-k)];
                        seqs[count] = sequence;
                        count++;
                    }
                    sequence.clear();
                }
            }
        }
        output << inputarray[x] << "-" << inputarray[y] << "\n";
        output << "Score: " << maxElement << " Sequence(s):";
        if (count > 0)
        {
            for (int i = 0; i < count; i++)
            {
                output << " \"" <<  *(seqs+count) << "\"";
            }
        }
        output << "\n";
    };
};

int main()
{
    string file;
	cin >> file;
	ifstream inputs;
    string input;
    Cell cell;
    inputs.open(file);
	while (!inputs.eof())
	{
		inputs >> input;
        cell.inputarray.push_back(input);
	}
	inputs.close();
    sort(cell.inputarray.begin(), cell.inputarray.end());
    int n, m;
    int size = cell.inputarray.size();
    for (int x = 0 ;x < size; x++)
    {
        n = cell.inputarray[x].size();
        Cell** matrix = new Cell*[n+1];
        for (int y = x+1; y < size; y++)
        {
            m = cell.inputarray[y].size();
            matrix[x] = new Cell[m+1];
            cell.fill_zero(matrix, x, y);
            cell.fill_matrix(matrix, x, y);
            cell.traceback_and_print(matrix, x, y);
            for (int i = 0; i < (n+1); ++i) 
            {
                delete [] matrix[i];
            }
            delete [] matrix;
        }
    }
    return 0;
}