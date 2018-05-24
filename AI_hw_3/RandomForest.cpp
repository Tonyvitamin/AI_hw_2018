#include "RandomForest.hpp"
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;

/// init a Random Forest  
RandomForest::RandomForest(int n_tree, int n_fearture){
    this->n_trees = n_tree;
    this->n_features = n_fearture;
    for(int i = 0 ; i<n_tree;i++){
        trees.push_back(CARTreeNode());
    }
}
// Random forest train
/* Change here to train differnet number of data  */
// In "Iris.txt" case, I only use the following two case
////// 30  data for train and select 15 for actual train <=> 150 data for test 
////// 
////// 120 data for train and select 100 for actual train <=> 30  data for test
////// 
void RandomForest::RandomForest_train(matrix & m){
    cout<<"Each tree of this forest is trained by 15 random data from "<<m.n_rows()<<" data"<<endl;
    //cout<<"Each tree of this forest is trained by 100 random data from "<<m.n_rows()<<" data"<<endl;

    cout<<"Number of decision tree is "<<trees.size()<<endl;

    // set up index for all attributes field //
    vector<int> all_columns = range(m.n_columns()-1);
    for(int i=0;i<trees.size();i++){
        CARTreeNode & tree = trees[i];
        srand(time(0));
        random_shuffle(all_columns.begin(), all_columns.end());

        //// Make selection here ////
        vector<int> rows = range(30);
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (rows.begin(), rows.end(), std::default_random_engine(seed));
        rows.resize(15);
        vector<int> training_cols = range(m.n_columns());
        matrix training = m.submatrix(rows, training_cols);

        tree.CART_train(training, all_columns);
    }
}
/// Random forest classify
/// It will return the expected class which the Random Forest classify the test data(row) into 
/// As for "iris.txt", set the class number for the convenient to experiment 
int RandomForest::RF_classify(vector<double> & row){
    int class_number[3]={0};

    /// count the possibility distribution of each tree
	for(int i = 0; i < n_trees; i++) {
		CARTreeNode & tree = trees[i];
        double max_possibility = 0;
        int max_index = 50;
		vector<double> distribution = tree.CART_classify(row);
        for(int j = 0 ; j<distribution.size();j++){
            if(distribution[j]>max_possibility){
                max_index = j;
                max_possibility = distribution[j];
            }
        }
        class_number[max_index]++;
    }

    /// select the most one as the vote result 
    int index =50;
    int lower_bound = 0;
    for(int i = 0 ; i<3;i++){
        if(class_number[i]>lower_bound){
            lower_bound = class_number[i];
            index = i;
        }
    }
    return index;
}