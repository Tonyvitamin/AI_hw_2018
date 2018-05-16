#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib> 
#include <string>
#include <vector>

//#include "matrix.hpp"
#include "RandomForest.hpp"
using namespace std;
/*
void fold_and_test(matrix & input_matrix){
    matrix m = input_matrix.shuffled();
    CARTreeNode root = CARTreeNode();
    root.CART_train
}
*/
int train_and_test(matrix &m){
    int n_attributes = m.n_columns();
    RandomForest * RF = new RandomForest(1, n_attributes);

    // train whole data
    RF->RandomForest_train(m);
    // test the whole data
	int right = 0;
	int wrong = 0;
	for(int i = 0; i < m.n_rows(); i++) {
		vector<double> & row = m.elements[i];
		int actual_class = RF->RF_classify(row);
		//classes.push_back(actual_class);
		int expected_class = row[m.n_columns()-1];
		if(actual_class == expected_class) {
			right++;
		}
		else {
			wrong++;
		}
	}
	double percent = right * 100.0 / m.n_rows();
	return percent;

    // train only the training data
    // to be continued
}

int main(){
    //fstream f1("iris.txt");
    matrix m;
    m.load("iris.txt");
    double correct_rate = train_and_test(m);
    cout<<"Correction rate is"<<" "<<correct_rate<<endl;
 
}