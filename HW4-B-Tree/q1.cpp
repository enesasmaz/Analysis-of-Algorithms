/*
ENES ŞAŞMAZ 150170090 FINAL HOMEWORK(HW4) PART1
HACKERRANK NAME: sasmaz17
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct xyz
{
	int x;
	int y;
	char z;
} xyz_struct;

class BTreeNode 
{ 
	xyz *keys; 
	int t;	 
	BTreeNode **C; 
	int n;	 
	bool leaf; 
public: 
	BTreeNode(int _t, bool _leaf); 
	void insertNonFull(int k, int l, char m, char key_input); 
	void splitChild(int i, BTreeNode *y); 
	void traverse(); 
friend class BTree; 
}; 


class BTree 
{ 
	BTreeNode *root; 
	int t; 
public: 
	BTree(int _t) 
	{ root = NULL; t = _t; } 
	void traverse() 
	{ if (root != NULL) root->traverse(); } 
	void insert(int k, int l, char m, char key_input);
}; 


BTreeNode::BTreeNode(int t1, bool leaf1) 
{
	t = t1; 
	leaf = leaf1; 
	keys = new struct xyz[2*t-1];
	C = new BTreeNode *[2*t];
	n = 0; 
} 


void BTreeNode::traverse() 
{ 
	for(int i=0 ; i < n ; i++){
        cout<<"("<<(keys+i)->x<<","<<(keys+i)->y<<","<<(keys+i)->z<<")";
    }
    cout << endl;

    for (int i = 0; i < n + 1; i++) {
        if (leaf == false)
            C[i]->traverse();
    }
} 

void BTree::insert(int k, int l, char m, char key_input) 
{ 
	if (root == NULL) 
	{ 
		root = new BTreeNode(t, true); 
		xyz_struct.x = k;
		xyz_struct.y = l;
		xyz_struct.z = m;
		root->keys[0] = xyz_struct; 
		root->n = 1; 
	} 
	else 
	{ 		
		if (root->n == 2*t-1) 
		{ 	
			BTreeNode *s = new BTreeNode(t, false); 
			s->C[0] = root; 
			s->splitChild(0, root); 
			int i = 0; 
			if (key_input == 'x')
			{
				if (s->keys->x < k) 
					i++; 
				s->C[i]->insertNonFull(k, l, m, key_input);
			} 
			if (key_input == 'y')
			{
				if (s->keys->y < l) 
					i++; 
				s->C[i]->insertNonFull(k, l, m, key_input);
			}
			if (key_input == 'z')
			{
				if (s->keys->z < m) 
					i++; 
				s->C[i]->insertNonFull(k, l, m, key_input);
			} 
			root = s; 
		} 
		else 
			root->insertNonFull(k, l, m, key_input); 
	} 
} 

void BTreeNode::insertNonFull(int k, int l, char m, char key_input) 
{ 
	int i = n-1; 
	if (leaf == true) 
	{ 
		if (key_input == 'x')
		{
			while (i >= 0 && (keys+i)->x > k) 
			{ 
				keys[i+1] = keys[i]; 
				i--; 
			} 
		}
		if (key_input == 'y')
		{
			while (i >= 0 && (keys+i)->y > l) 
			{ 
				keys[i+1] = keys[i]; 
				i--; 
			} 
		}
		if (key_input == 'z')
		{
			while (i >= 0 && (keys+i)->z > m) 
			{ 
				keys[i+1] = keys[i]; 
				i--; 
			} 
		}
		xyz_struct.x = k;
		xyz_struct.y = l;
		xyz_struct.z = m;
		keys[i+1] = xyz_struct; 
		n = n+1; 
	} 
	else 
	{ 
		if (key_input == 'x')
		{
			while (i >= 0 && (keys+i)->x > k) 
			{
				i--; 
			}		
		}
		if (key_input == 'y')
		{
			while (i >= 0 && (keys+i)->y > l) 
			{
				i--; 
			}		
		}
		if (key_input == 'z')
		{
			while (i >= 0 && (keys+i)->z > m) 
			{
				i--; 
			}		
		}
		if (C[i+1]->n == 2*t-1) 
		{ 
			splitChild(i+1, C[i+1]); 
			if (key_input == 'x')
			{
				if ((keys+(i+1))->x < k) 
				{	
					i++; 
				}
			}
			if (key_input == 'y')
			{
				if ((keys+(i+1))->y < l) 
				{	
					i++; 
				}
			}			
			if (key_input == 'z')
			{
				if ((keys+(i+1))->z < m) 
				{	
					i++; 
				}
			}
		} 
		C[i+1]->insertNonFull(k, l, m, key_input); 
	} 
} 

void BTreeNode::splitChild(int i, BTreeNode *y) 
{ 
	BTreeNode *z = new BTreeNode(y->t, y->leaf); 
	z->n = t - 1; 
	for (int j = 0; j < t-1; j++) 
		z->keys[j] = y->keys[j+t]; 
	if (y->leaf == false) 
	{ 
		for (int j = 0; j < t; j++) 
			z->C[j] = y->C[j+t]; 
	} 
	y->n = t - 1; 
	for (int j = n; j >= i+1; j--) 
		C[j+1] = C[j]; 
	C[i+1] = z; 
	for (int j = n-1; j >= i; j--) 
		keys[j+1] = keys[j]; 
	keys[i] = y->keys[t-1]; 
	n = n + 1; 
} 

int main() 
{ 
	int totalnode, degree;
	char key_input;
	cin >> totalnode;
	cin >> degree;
	cin >> key_input;
	BTree t(degree); 
	for (int i = 0; i < totalnode; i++)
	{
		int x,y;
		char z;
		cin >> x;
		cin >> y;
		cin >> z;
		t.insert(x, y, z, key_input);
	}
	t.traverse(); 

	return 0; 
} 
