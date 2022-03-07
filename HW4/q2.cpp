/***********************************************************
STUDENT INFORMATION
Full Name : Enes Şaşmaz
Student ID: 150170090
**********************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <limits>
#include <float.h>

using namespace std;

struct Point{
    int xCoordinate;
    int yCoordinate;
};

class PointSpace{
    int numberOfPoints;
    vector<Point> points;

public:
    void setNumberOfPoints(int n){
        numberOfPoints = n;
    }
    
    int getNumberOfPoints(){
        return numberOfPoints;
    }
    
    void addPoint(int x, int y){
        Point p = Point();
        p.xCoordinate = x;
        p.yCoordinate = y;
        
        points.push_back(p);
    }
    
    
    void printNumberOfPoints(){
        cout << "Total number of points: " << getNumberOfPoints() << endl;
    }
    
    void printAllPoints(){
        cout << "Points coordinates (x y): " << endl;
        
        for (std::vector<Point>::const_iterator i = points.begin(); i != points.end(); ++i){
            cout << i->xCoordinate << "\t" << i->yCoordinate << endl;
        }
    }
    
      
    /******************** MY FUNCTIONS ********************/
    // It is used to sort arrays by x coordinate.
    void sortx(Point arr[], int n)
    {
        if (n == 1)
            return;
        for (int i=0; i<n-1; i++)
            if (arr[i].xCoordinate > arr[i+1].xCoordinate)
                swap(arr[i], arr[i+1]);
        sortx(arr, n-1);
    }
    // It is used to sort arrays by y coordinate.
    void sorty(Point arr[], int n)
    {
        if (n == 1)
            return;
        for (int i=0; i<n-1; i++)
            if (arr[i].yCoordinate > arr[i+1].yCoordinate)
                swap(arr[i], arr[i+1]);
        sortx(arr, n-1);
    }
    // It is used to find the distance between two points.
    float dist(Point p1, Point p2)
    {
        return sqrt((p1.xCoordinate - p2.xCoordinate)*(p1.xCoordinate - p2.xCoordinate) + (p1.yCoordinate - p2.yCoordinate)*(p1.yCoordinate - p2.yCoordinate));
    }
    // A Brute Force method to return the smallest distance between two points.
    float bruteForce(Point P[], int n)
    {
        float min = FLT_MAX;
        for (int i = 0; i < n; ++i)
            for (int j = i+1; j < n; ++j)
                if (dist(P[i], P[j]) < min)
                    min = dist(P[i], P[j]);
        return min;
    }
    // It is used to get min.
    float min(float x, float y)
    {
        return (x < y)? x : y;
    }
    // A utility function to find the distance between the closest points of strip of given size. 
    float stripClosest(Point strip[], int size, float d)
    {
        float min = d;
        sorty(strip, size);
        for (int i = 0; i < size; ++i)
            for (int j = i+1; j < size && (strip[j].yCoordinate - strip[i].yCoordinate) < min; ++j)
                if (dist(strip[i],strip[j]) < min)
                    min = dist(strip[i], strip[j]);
    
        return min;
    }  
    // A recursive function to find the smallest distance.
    float closestUtil(Point P[], int n)
    {
        if (n <= 3)
            return bruteForce(P, n);
        int mid = n/2;
        Point midPoint = P[mid];
        float dl = closestUtil(P, mid); 
        float dr = closestUtil(P + mid, n - mid);
        float d = min(dl, dr);
        Point strip[n];
        int j = 0;
        for (int i = 0; i < n; i++)
            if (abs(P[i].xCoordinate - midPoint.xCoordinate) < d)
                strip[j] = P[i], j++;
        return min(d, stripClosest(strip, j, d) );
    } 
    /******************************************************/
    double FindClosestPairDistance(){
        // FILL HERE
        int n = points.size();
        Point arr[n];
        for (int i = 0; i < n; i++) {
            arr[i] = points[i];
        }
        sortx(arr, numberOfPoints);
        return closestUtil(arr, numberOfPoints);
        // You may define new functions if you need
    }
};



int main(int argc, char* argv[]){
    //define a point space
    PointSpace pointSpace;

    //get file name
    string inputFileName = argv[1];
    
    string line;
    ifstream infile(inputFileName);

    //read the number of total points (first line)
    getline(infile, line);
    pointSpace.setNumberOfPoints(stoi(line));

    //read points' coordinates and assign each point to the space (second to last line)
    int x, y;
    while (infile >> x >> y){
       pointSpace.addPoint(x, y);
    }
    
    //print details of point space (not necessary for assignment evaluation: calico will not check this part)
    pointSpace.printAllPoints();
    pointSpace.printNumberOfPoints();
    
    //find and print the distance between closest pair of points (calico will check this part)
    double closestDistance = pointSpace.FindClosestPairDistance();
    cout << "Distance between the closest points: " << closestDistance << endl;
    
    return 0;
}



