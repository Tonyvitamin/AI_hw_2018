#include "CART.hpp"

#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;


// initiate function 
CARTreeNode::CARTreeNode(){
    left = right = NULL;
	attribute = -1;
    threshold_value = 1337.1337;
	gain = -1337.0;
}
// function used to destroy the node 
CARTreeNode::~CARTreeNode(){
	if(left != NULL) {
		delete left;
	}
	if(right != NULL) {
		delete right;
	}
}
// sort values of a specific attribute and calculate a series of threshold values then return the threshold_value 
vector<double> value_sort(vector<double> samples){

    vector<double> split_value;
    /// In case of the single sample, just return the value itself
    if(samples.size() == 1){
        split_value.push_back(samples[0]);
        return split_value;
    }

    vector<double> temp;
    for(int i = 0 ;i<samples.size();i++)
        temp.push_back(samples[i]);
    sort(temp.begin(), temp.end());

    for(int i = 0 ; i < temp.size()-1 ; i++){
        // use "mean of two's sum" as threshold_value
        split_value.push_back((temp[i]+temp[i+1])/2);
    }
    return split_value;
}
// split the samples into lesser and greater 
void split_two_group(vector<double>  samples, vector<double> & class_label, double value, vector<double> &lesser, vector<double> &greater){
    for(int i =0 ; i<samples.size();i++){
        if(samples[i]<=value){
            lesser.push_back(class_label[i]);
        }
        else {
            greater.push_back(class_label[i]);
        }
    }
}

// convert class list  into class cluster distribution
// i.e.  classes[0] = 10 , classes[1] = 3 , classes[2] = 2 , with the list containing 15 object
vector<int> list_to_discrete(const vector<double> & list, int num_classes) {
	vector<int> classes(num_classes, 0);
	for(int i = 0; i < list.size(); i++) {
		int cls = (int)list[i];
		assert(cls >= 0);
		assert(cls < num_classes);
		classes[cls] += 1;
	}
	return classes;
}
// convert to probability for each class
// i.e. p[0] = 0.3 , p[1] = 0.4 , p[2] = 0.3 
vector<double> discrete_p_values(const vector<double> & list, int num_classes) {
	vector<int> discrete = list_to_discrete(list, num_classes);
	vector<double> p_values;
	for(int i = 0; i < num_classes; i++) {
		int count = discrete[i];
		double p = ((double) count) / list.size();
		p_values.push_back(p);
	} 
	return p_values;
}
/// function to calculate gini index for single group
/// still need a conversion between string and integer for computation 
double gini_impurity(vector<double> & class_label, int n_class){

    if(class_label.size()==0)
        return 0.0;
    vector<double> p_values = discrete_p_values(class_label, n_class);
	double result = 1.0;
	for(int i = 0; i < p_values.size(); i++) {
		double p = p_values[i];
		result -= p * p;
	}
    return result;
}
// function to calculate gini gain 
double gini_gain(vector<double>  parent_group, vector<double>  childA, vector<double>  childB , int n_class){
    double child_impurity, parent_impurity;
    child_impurity = gini_impurity(childA, n_class) * childA.size() / parent_group.size();
    child_impurity += gini_impurity(childB, n_class) * childB.size() / parent_group.size(); 
    parent_impurity = gini_impurity(parent_group, n_class);  
    return parent_impurity - child_impurity;
}
void CARTreeNode::CART_train(matrix &m , vector<int> attributes){
    

    // random subset of attriubte 
    random_shuffle(attributes.begin(), attributes.end());
    vector<int> subset = attributes;

    // Section to change attributes used to split a node
    // In "iris.txt" can change from 1 to 4 attributes
    //attributes.resize(1);
    attributes.resize(2);
    //attributes.resize(3);
    //attributes.resize(4);

    /// class value
    vector<double> class_label = m.column(-1);

	//Elements used to decide which column and value to split on
	double max_gain = -10000.0;
	int max_col = 0;
	double max_value = 0.0;

    // for each attributes used to split a node 
    for(int i = 0 ; i<attributes.size();i++){
        int attribute = attributes[i];

        vector<double> samples = m.column(attribute);

        vector<double> split_value = value_sort(samples);
        // for all the possible threshold values, choose the best one 
        for(int j = 0 ; j<split_value.size(); j++){
            vector<double> lesser, greater;
            int split_v = split_value[j];
            split_two_group(m.column(attribute), class_label, split_v, lesser, greater);
            double gain_here = gini_gain(class_label, lesser, greater, 3);
            if(max_gain < gain_here){
                max_gain = gain_here;
                max_col = attribute;
                max_value = split_value[j];
            }
        }
    }

    // save split values
    this->attribute = max_col;
    this->threshold_value = max_value;
    this->gain = max_gain; 

    // split the node into two matrix
    matrix l, r;
    m.split(max_col, max_value, l, r);

    /// tree limitation 
    /// minimum number of samples in a node
    if(l.elements.size()<=0||r.elements.size()<=0){
        this->distribution = discrete_p_values(class_label , 3);
        return;
    }

    this->left = new CARTreeNode();
    left->CART_train(l, subset);
    this->right = new CARTreeNode();
    right->CART_train(r, subset);
}

/// classification for each data 
vector<double> CARTreeNode::CART_classify(vector<double> & row){
	if(distribution.size() > 0) {
		return distribution;
	}
	if(row[attribute] <= threshold_value) {
		assert(left != NULL);
		return left->CART_classify(row);
	}
	else {
		assert(right != NULL);
		return right->CART_classify(row);
	}
}