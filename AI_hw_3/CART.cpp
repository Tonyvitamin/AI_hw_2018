#include "CART.hpp"

#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;



CARTreeNode::CARTreeNode(){
    left = right = NULL;
	attribute = -1;
    threshold_value = 1337.1337;
	gain = -1337.0;
}
CARTreeNode::~CARTreeNode(){
	if(left != NULL) {
		delete left;
	}
	if(right != NULL) {
		delete right;
	}
}
vector<double> value_sort(vector<double> &samples){
    vector<double> temp;
    for(int i = 0 ;i<samples.size();i++)
        temp.push_back(samples[i]);
    sort(temp.begin(), temp.end());
    vector<double> split_value;
    for(int i = 0 ; i < temp.size()-1 ; i++){
        split_value.push_back((temp[i]+temp[i+1])/2);
    }
    return split_value;
}

void split_two_group(vector<double>  samples, vector<double> & class_label, double value, vector<double> lesser, vector<double> greater){
    for(int i =0 ; i<samples.size();i++){
        //cout<<"Sample value is "<<samples[i]<<" while threshold is "<<value<<" "<<i<<endl;
        if(samples[i]<value){
            lesser.push_back(class_label[i]);
        }
        else {
            greater.push_back(class_label[i]);
        }
    }
    cout<<"split two group just working fine"<<endl;
}

/*
Convert a list of numbers into a class distribution
*/
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

vector<double> discrete_p_values(const vector<double> & list, int num_classes) {
	//Convert list to discrete RV
	vector<int> discrete = list_to_discrete(list, num_classes);
	//Convert to probability values
	vector<double> p_values;
	for(int i = 0; i < num_classes; i++) {
		int count = discrete[i];
		double p = ((double) count) / list.size();
		p_values.push_back(p);
	} 
	return p_values;
}
/// still need a conversion between string and integer for computation 
double gini_impurity(vector<double> & class_label, int n_class){

    vector<double> p_values = discrete_p_values(class_label, n_class);
	printf("p_values[0]=%f, p_values[1]=%f, p_values[2]=%f\n", p_values[0], p_values[1], p_values[2]);
	double result = 1.0;
	for(int i = 0; i < p_values.size(); i++) {
		double p = p_values[i];
		result -= p * p;
	}
    cout<<"gini impurity is "<< result<<endl;
    return result;
}

double gini_gain(vector<double> & parent_group, vector<double> & childA, vector<double> & childB , int n_class){
    double child_impurity, parent_impurity;
    child_impurity = gini_impurity(childA, n_class) * childA.size() / parent_group.size();
    child_impurity += gini_impurity(childB, n_class) * childB.size() / parent_group.size(); 
    parent_impurity = gini_impurity(parent_group, n_class);  
    return parent_impurity - child_impurity;
}
void CARTreeNode::CART_train(matrix &m , vector<int> attributes){

    // random subset of attriubte 
    /*random_shuffle(attributes.begin(), attributes.end());
    attributes.resize(3);*/

    /// class value
    vector<double> class_label = m.column(-1);
	//Decide which column to split on
	double max_gain = -10000.0;
	int max_col = 0;
	double max_value = 0.0;

    for(int i = 0 ; i<attributes.size();i++){
        int attribute = attributes[i];
        vector<double> samples = m.column(attribute);
        vector<double> split_value = value_sort(samples);
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
    double MINIMUM_GAIN = 0.001;

    //// set up a lower bound of purity gain 
    if(max_gain <  MINIMUM_GAIN){
        distribution = discrete_p_values(class_label , 3);
        return;
    }

    // save split values
    this->attribute = max_col;
    this->threshold_value = max_value;
    this->gain = max_gain; 

    // split the node into two matrix
    matrix l, r;
    m.split(max_col, max_value, l, r);

    this->left = new CARTreeNode();
    left->CART_train(l, attributes);
    right = new CARTreeNode();
    right->CART_train(r, attributes);
}

/// classification for each data 
vector<double> CARTreeNode::CART_classify(vector<double> & row){
	if(distribution.size() > 0) {
		return distribution;
	}
	if(row[attribute] < threshold_value) {
		assert(left != NULL);
		return left->CART_classify(row);
	}
	else {
		assert(right != NULL);
		return right->CART_classify(row);
	}
}