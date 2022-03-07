/*
ENES ŞAŞMAZ 150170090 FINAL HOMEWORK(HW4) PART2
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
    int findKey(int k, int l, char m, char key_input); 
    void remove(int k, int l, char m, char key_input);
    void removeFromLeaf(int idx); 
    void removeFromNonLeaf(int idx, char key_input);
    xyz getPred(int idx); 
    xyz getSucc(int idx);
    void fill(int idx); 
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx); 
    void merge(int idx); 
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
    void remove(int k, int l, char m, char key_input);
}; 


BTreeNode::BTreeNode(int t1, bool leaf1) 
{
	t = t1; 
	leaf = leaf1; 
	keys = new struct xyz[2*t-1];
	C = new BTreeNode *[2*t];
	n = 0; 
} 

int BTreeNode::findKey(int k, int l, char m, char key_input) 
{ 
    int idx=0; 
    if (key_input == 'x')
    {
        while (idx<n && (keys + idx)->x < k) 
            ++idx; 
        return idx; 
    }
    if (key_input == 'y')
    {
        while (idx<n && (keys + idx)->y < l) 
            ++idx; 
        return idx; 
    }
    if (key_input == 'z')
    {
        while (idx<n && (keys + idx)->z < m) 
            ++idx; 
        return idx; 
    }
    else
    {
        return 0;
    }
}

void BTreeNode::remove(int k, int l, char m, char key_input) 
{ 
    int idx = findKey(k, l, m, key_input); 
    if (key_input == 'x')
    {  
        if (idx < n && (keys + idx)->x == k) 
        { 
            if (leaf) 
                removeFromLeaf(idx); 
            else
                removeFromNonLeaf(idx, key_input); 
        } 
        else
        { 
            if (leaf) 
            {
                return; 
            } 
            bool flag = ( (idx==n)? true : false ); 
            if (C[idx]->n < t) 
                fill(idx); 
            if (flag && idx > n) 
                C[idx-1]->remove(k, l, m, key_input); 
            else
                C[idx]->remove(k, l, m, key_input); 
        } 
        return; 
    }
    if (key_input == 'y')
    {  
        if (idx < n && (keys + idx)->y == l) 
        { 
            if (leaf) 
                removeFromLeaf(idx); 
            else
                removeFromNonLeaf(idx, key_input); 
        } 
        else
        { 
            if (leaf) 
            {
                return; 
            } 
            bool flag = ( (idx==n)? true : false ); 
            if (C[idx]->n < t) 
                fill(idx); 
            if (flag && idx > n) 
                C[idx-1]->remove(k, l, m, key_input); 
            else
                C[idx]->remove(k, l, m, key_input); 
        } 
        return; 
    }
    if (key_input == 'z')
    {  
        if (idx < n && (keys + idx)->z == m) 
        { 
            if (leaf) 
                removeFromLeaf(idx); 
            else
                removeFromNonLeaf(idx, key_input); 
        } 
        else
        { 
            if (leaf) 
            {
                return; 
            } 
            bool flag = ( (idx==n)? true : false ); 
            if (C[idx]->n < t) 
                fill(idx); 
            if (flag && idx > n) 
                C[idx-1]->remove(k, l, m, key_input); 
            else
                C[idx]->remove(k, l, m, key_input); 
        } 
        return; 
    }
} 

void BTreeNode::removeFromLeaf (int idx) 
{ 
    for (int i=idx+1; i<n; ++i) 
        keys[i-1] = keys[i];
    n--;
    return;
}
  
void BTreeNode::removeFromNonLeaf(int idx, char key_input) 
{ 
  
    int temp1 = (keys + idx)->x;  
    int temp2 = (keys + idx)->y;  
    char temp3 = (keys + idx)->z;  
    if (C[idx]->n >= t) 
    { 
        xyz pred = getPred(idx); 
        (keys + idx)->x = pred.x; 
        (keys + idx)->y = pred.y; 
        (keys + idx)->z = pred.z; 
        C[idx]->remove(pred.x, pred.y, pred.z, key_input); 
    } 
    else if (C[idx+1]->n >= t) 
    { 
        xyz succ = getSucc(idx); 
        (keys + idx)->x = succ.x; 
        (keys + idx)->y = succ.y; 
        (keys + idx)->z = succ.z;
        C[idx+1]->remove(succ.x, succ.y, succ.z, key_input); 
    } 
    else
    { 
        merge(idx); 
        C[idx]->remove(temp1, temp2, temp3, key_input); 
    } 
    return; 
} 
  
xyz BTreeNode::getPred(int idx) 
{
    BTreeNode *cur=C[idx]; 
    while (!cur->leaf) 
        cur = cur->C[cur->n]; 
    return cur->keys[cur->n-1]; 
} 

xyz BTreeNode::getSucc(int idx) 
{
    BTreeNode *cur = C[idx+1]; 
    while (!cur->leaf) 
        cur = cur->C[0]; 
    return cur->keys[0]; 
} 

void BTreeNode::fill(int idx) 
{ 
    if (idx!=0 && C[idx-1]->n>=t) 
        borrowFromPrev(idx); 
    else if (idx!=n && C[idx+1]->n>=t) 
        borrowFromNext(idx);
    else
    { 
        if (idx != n) 
            merge(idx); 
        else
            merge(idx-1); 
    } 
    return; 
} 
  
void BTreeNode::borrowFromPrev(int idx) 
{ 
    BTreeNode *child=C[idx]; 
    BTreeNode *sibling=C[idx-1]; 
    for (int i=child->n-1; i>=0; --i) 
        child->keys[i+1] = child->keys[i]; 
    if (!child->leaf) 
    { 
        for(int i=child->n; i>=0; --i) 
            child->C[i+1] = child->C[i]; 
    } 
    child->keys[0] = keys[idx-1];  
    if(!child->leaf) 
        child->C[0] = sibling->C[sibling->n]; 
    keys[idx-1] = sibling->keys[sibling->n-1]; 
    child->n += 1; 
    sibling->n -= 1; 
    return; 
} 

void BTreeNode::borrowFromNext(int idx) 
{ 
    BTreeNode *child=C[idx]; 
    BTreeNode *sibling=C[idx+1]; 
    child->keys[(child->n)] = keys[idx]; 
    if (!(child->leaf)) 
        child->C[(child->n)+1] = sibling->C[0]; 
    keys[idx] = sibling->keys[0]; 
    for (int i=1; i<sibling->n; ++i) 
        sibling->keys[i-1] = sibling->keys[i]; 
    if (!sibling->leaf) 
    { 
        for(int i=1; i<=sibling->n; ++i) 
            sibling->C[i-1] = sibling->C[i]; 
    } 
    child->n += 1; 
    sibling->n -= 1; 
    return; 
} 

void BTreeNode::merge(int idx) 
{ 
    BTreeNode *child = C[idx]; 
    BTreeNode *sibling = C[idx+1]; 
    child->keys[t-1] = keys[idx]; 
    for (int i=0; i<sibling->n; ++i) 
        child->keys[i+t] = sibling->keys[i]; 
    if (!child->leaf) 
    { 
        for(int i=0; i<=sibling->n; ++i) 
            child->C[i+t] = sibling->C[i]; 
    } 
    for (int i=idx+1; i<n; ++i) 
        keys[i-1] = keys[i]; 
    for (int i=idx+2; i<=n; ++i) 
        C[i-1] = C[i]; 
    child->n += sibling->n+1; 
    n--; 
    delete(sibling); 
    return; 
} 

void BTree::remove(int k, int l, char m, char key_input) 
{ 
    if (!root) 
    { 
        return; 
    }
    root->remove(k, l, m, key_input); 
    if (root->n==0)
    { 
        BTreeNode *tmp = root; 
        if (root->leaf) 
            root = NULL; 
        else
            root = root->C[0]; 
        delete tmp; 
    } 
    return; 
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
    int x,y;
	char z;
	for (int i = 0; i < totalnode; i++)
	{
		cin >> x;
		cin >> y;
		cin >> z;
		t.insert(x, y, z, key_input);
	}
	
    if (key_input == 'x')
    {
        cin >> x;
        t.remove(x,y,z,key_input);
    }
    if (key_input == 'y')
    {
        cin >> y;
        t.remove(x,y,z,key_input);
    }
    if (key_input == 'z')
    {
        cin >> z;
        t.remove(x,y,z,key_input);
    }
    t.traverse(); 

	return 0; 
} 
