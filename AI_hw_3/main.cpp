#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib> 
#include <string>
#include <vector>

#include "RandomForest.hpp"
using namespace std;

/* train and test use the same data */
double with_all_data(matrix &m){
    int n_attributes = m.n_columns();
    RandomForest * RF = new RandomForest(10, n_attributes);

    // train whole data
    RF->RandomForest_train(m);
    // test the whole data
	int right = 0;
	int wrong = 0;
	for(int i = 0; i < m.n_rows(); i++) {
		vector<double> & row = m.elements[i];
		int actual_class = RF->RF_classify(row);
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
}

int train_and_test(matrix &m){
    
    // separate training data and testing data randomly with 120 : 30
	// change here and RandomForest.cpp 36~39 to test different data set
    matrix inputm = m.shuffled();
    vector<int> all_columns = range(m.n_columns());
    vector<int> training_rows = range(30);
    vector<int> testing_rows ;
    for(int i = 30 ; i<150;i++)
        testing_rows.push_back(i);
    
    int n_attributes = m.n_columns()-1;
	////// change here to test different number of trees forming a random forest
    RandomForest * RF = new RandomForest(100, n_attributes);
    matrix training = inputm.submatrix(training_rows, all_columns);
    matrix testing = inputm.submatrix(testing_rows, all_columns);
    RF->RandomForest_train(training);

    /* classify training data */
    int right = 0;
	int wrong = 0;
	for(int i = 0; i < training.n_rows(); i++) {
		vector<double> & training_row = training.elements[i];
		int actual_class = RF->RF_classify(training_row);
		int expected_class = training_row[training.n_columns()-1];
		if(actual_class == expected_class) {
			right++;
		}
		else {
			wrong++;
		}
	}
	double percent = right * 100.0 / training.n_rows();
    cout<<"Training data:\nCorrection rate is "<<percent<<" %"<<endl;

    /* classify test data */
    right = 0;
    wrong = 0;
	for(int i = 0; i < testing.n_rows(); i++) {
		vector<double> & testing_row = testing.elements[i];
		int actual_class = RF->RF_classify(testing_row);
		int expected_class = testing_row[testing.n_columns()-1];
		if(actual_class == expected_class) {
			right++;
		}
		else {
			wrong++;
		}
	}
	percent = right * 100.0 / testing.n_rows();
	return percent;

}

int main(){
    matrix m;
	// read the input file
    m.load("iris.txt");
    double correct_rate = train_and_test(m);
    cout<<"Testing data :\nCorrection rate is "<<correct_rate<<" %"<<endl;
 
}