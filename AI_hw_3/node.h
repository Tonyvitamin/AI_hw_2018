#include<iostream>
#include<vector>
#include<string>



using namespace std;

struct node{
	string class_name;  // class belong
	int split_attr;     // attribute used to split
	int node_type;	    // node type
	double threshold;   // threshold for each attribute
	vector<int> attr;
	vector<node*> childrenNode; 	
};


void sort();


