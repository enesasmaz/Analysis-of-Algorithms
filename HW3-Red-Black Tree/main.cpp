// ENES ŞAŞMAZ
// 150170090
// HOMEWORK-3
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

enum Color {RED, BLACK}; 

struct Node	//A Struct with name, team, rebound, assist, point, color, left child, right child, and parent.
{ 
	string name, team; 
	int rebound, assist, point;
    bool color; 
	Node *left, *right, *parent;
	Node(string name, string team, int rebound, int assist, int point)
	{ 
        this->name = name; 
		this->team = team;   
		this->rebound = rebound;  
		this->assist = assist; 
		this->point = point; 
        left = NULL;
        right = NULL;
        parent = NULL; 
        this->color = RED; 
	} 
}; 

class Tree    //A class with root pointers, pointers created for max values, rotate and fix functions, insert and print functions, and find max functions.
{ 
public: 
	Node *root; 
	Node *maxp;
	Node *maxa;
	Node *maxr;
	void rotateLeft(Node *&, Node *&); 
	void rotateRight(Node *&, Node *&); 
	void fixViolation(Node *&, Node *&); 
	void insert(string name, string team, int rebound, int assist, int point); 
	void preorder();
	void findmax_point(Node *root);
	void findmax_assist(Node *root);
	void findmax_rebound(Node *root);
	Tree() { root = NULL; maxp = NULL; maxa = NULL; maxr = NULL; } 
}; 

int getLevelfunc(Node *iter, string data, int first_level) //Finding level of node
{ 
    if (iter == NULL) 
    {
		return 0;	//if tree not exist
	}
    if (iter->name == data) 
    {    
		return first_level; //if searching data found
	}
    int downlevel = getLevelfunc(iter->left, data, first_level + 1); //go left child
    if (downlevel != 0)
	{ 
        return downlevel; 
	}
    downlevel = getLevelfunc(iter->right, data, first_level + 1); //go right child
    return downlevel; 
} 

int getLevel(Node *level) 
{ 
	Node *iter = level;
	while (iter->parent != NULL)
	{
		iter = iter->parent; //getting root of tree
	}
    return getLevelfunc(iter, level->name, 1); 
} 

void printPreorder(Node* node) 
{ 
    if (node == NULL) 
    {
        return; 	//if root not exist
    }
	int i_max = getLevel(node);
	for (int i = 0; i < (i_max - 1); i++)
	{
		cout << "-";
	}
	if (node->color==true)
	{
		cout << "(BLACK) "; //converting bool to string
	}
	if (node->color==false)
	{
		cout << "(RED)" ;  //converting bool to string
	}
	
	
	cout << node->name << endl; //preorder print
    printPreorder(node->left);  
    printPreorder(node->right); 	
} 

void update(Node *root, Node *&temp) //if same name player then update veriables of player
{
	root->point += temp->point;
	root->assist += temp->assist;
	root->rebound += temp->rebound;
	temp = root;
}

Node* insert_update(Node *root, Node *&temp) 
{
	if (root == NULL)
    {
	    return temp; //instert first element of tree
    }
	if (temp->name == root->name)
	{
		update(root, temp);	//update if temp and root have same name
	}
    else if (temp->name < root->name) 
	{ 
		root->left = insert_update(root->left, temp); //go to left child
		root->left->parent = root; //parent connection
	}
	else if (temp->name > root->name) 
	{ 
		root->right = insert_update(root->right, temp);  //go to right child
		root->right->parent = root; //parent connection
	} 
	return root; 
} 

void Tree::rotateLeft(Node *&root, Node *&temp) //If the uncle is black, either left or right rotate is done. this is the left rotate operation. 
{ 
	Node *temp_right = temp->right; 

	temp->right = temp_right->left; 

	if (temp->right != NULL)
		temp->right->parent = temp;

	temp_right->parent = temp->parent;

	if (temp->parent == NULL) 
		root = temp_right; 

	else if (temp == temp->parent->left) 
		temp->parent->left = temp_right; 

	else
		temp->parent->right = temp_right; 

	temp_right->left = temp; 
	temp->parent = temp_right; 
} 

void Tree::rotateRight(Node *&root, Node *&temp) //If the uncle is black, either left or right rotate is done. this is the right rotate operation.
{ 
	Node *temp_left = temp->left; 

	temp->left = temp_left->right; 

	if (temp->left != NULL) 
		temp->left->parent = temp; 

	temp_left->parent = temp->parent; 

	if (temp->parent == NULL) 
		root = temp_left; 

	else if (temp == temp->parent->left) 
		temp->parent->left = temp_left; 

	else
		temp->parent->right = temp_left; 

	temp_left->right = temp; 
	temp->parent = temp_left; 
} 

void Tree::fixViolation(Node *&root, Node *&temp) //In Red-Black tree, we use two tools to do balancing.
{ 
	Node *parent_temp = NULL; 
	Node *grand_parent_temp = NULL; 

	while ((temp != root) && (temp->color != BLACK) && 
		(temp->parent->color == RED)) 
	{ 
		parent_temp = temp->parent; 
		grand_parent_temp = temp->parent->parent; 

		if (parent_temp == grand_parent_temp->left) 
		{ 
			Node *uncle_temp = grand_parent_temp->right; 		///////
			if (uncle_temp != NULL && uncle_temp->color == RED) //
			{ 													//
				grand_parent_temp->color = RED; 				// Recoloring
				parent_temp->color = BLACK; 					//
				uncle_temp->color = BLACK; 						//
				temp = grand_parent_temp; 						///////
			} 
			else
			{ 
				if (temp == parent_temp->right) 				///////
				{ 												//
					rotateLeft(root, parent_temp); 				//
					temp = parent_temp; 						//
					parent_temp = temp->parent; 				//
				} 												// Rotation
				rotateRight(root, grand_parent_temp); 			//
				swap(parent_temp->color, 						//
						grand_parent_temp->color); 				//
				temp = parent_temp; 							///////
			} 
		} 
		else
		{ 
			Node *uncle_temp = grand_parent_temp->left; 			///////
																	//
			if ((uncle_temp != NULL) && (uncle_temp->color == RED)) //
			{ 														// Recoloring
				grand_parent_temp->color = RED; 					//
				parent_temp->color = BLACK; 						//
				uncle_temp->color = BLACK; 							//
				temp = grand_parent_temp; 							///////
			} 
			else
			{														
				if (temp == parent_temp->left) 						///////
				{ 													//
					rotateRight(root, parent_temp); 				//
					temp = parent_temp; 							//
					parent_temp = temp->parent; 					//
				} 													// Rotation
				rotateLeft(root, grand_parent_temp); 				//
				swap(parent_temp->color, 							//
						grand_parent_temp->color); 					//
				temp = parent_temp; 								///////
			} 
		} 
	} 

	root->color = BLACK; 
} 

void Tree::insert(string name, string team, int rebound, int assist, int point) 
{ 
	Node *temp = new Node(name, team, rebound, assist, point); //defining new node

	root = insert_update(root, temp); //insert that node to tree

	fixViolation(root, temp); //balancing after insert
} 

void Tree::preorder()
{  
    printPreorder(root); //run printPreorder
} 

void Tree::findmax_point(Node *root)	//finding max point value
{
	if (root==NULL)
		return;
	if (root->point>maxp->point)
		maxp=root;		//change if root point bigger than maxp point
    findmax_point(root->left); //go to left child
    findmax_point(root->right); //go to right child
}

void Tree::findmax_assist(Node *root)	//finding max assist value
{
	if (root==NULL)
		return;
	if (root->assist>maxa->assist)
		maxa=root;		//change if root assist bigger than maxa assist
    findmax_assist(root->left); //go to left child
    findmax_assist(root->right); //go to right child
}

void Tree::findmax_rebound(Node *root)	//finding max rebound value
{
	if (root==NULL)
		return;
	if (root->rebound>maxr->rebound)
		maxr=root;		//change if root rebound bigger than maxr rebound
	findmax_rebound(root->left); //go to left child
    findmax_rebound(root->right); //go to right child

}

int main(int argc, char *argv[])
{ 
	char* filename = argv[1];
	Tree tree; 
	ifstream file(filename);					////
												//
	if (!file.is_open())						// File operations
	{											//
		cout << "File cannot be opened!";		////
	}
	string year, name, team, s_rebound, s_assist, s_point, header, old_year;
	int rebound = 0;
	int assist = 0;
	int point = 0;
	int i = 0;
	old_year = "2000-2001"; //initialize first year
	getline(file, header); //this is the header line
	while (file.good()) //In this while loop, the necessary operations have been done to execute functions and print them. While it runs until it reaches the end of the file.
	{
		getline(file,year,',');
		if (old_year != year)
		{
			tree.maxp=tree.root;
			tree.findmax_point(tree.root);
			tree.maxa=tree.root;
			tree.findmax_assist(tree.root);
			tree.maxr=tree.root;
			tree.findmax_rebound(tree.root);
			cout << "End of the " << year << " Season" << endl;
			cout << "Max Points: " << tree.maxp->point << " - Player Name: " <<  tree.maxp->name << endl;
			cout << "Max Assists: " << tree.maxa->assist << " - Player Name: " <<  tree.maxa->name << endl;
			cout << "Max Rebs: " << tree.maxr->rebound << " - Player Name: " <<  tree.maxr->name << endl;
			if (i == 0)
				tree.preorder();
			i++;
		}
		getline(file,name,',');
		getline(file,team,',');
		getline(file,s_rebound,',');
		getline(file,s_assist,',');
		getline(file,s_point,'\n');
		rebound = stoi(s_rebound);
		assist = stoi(s_assist);
		point = stoi(s_point);
		tree.insert(name, team, rebound, assist, point);
		old_year = year;
	}

	return 0; 
} 