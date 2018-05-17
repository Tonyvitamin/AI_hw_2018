#include "RandomForest.hpp"


using namespace std;

template<typename T>
int inline negative_index_convert(std::vector<T> list, int index) {
    //TODO: Bounds checking?
    if(index >= 0) {
        return index;
    }
    else {
        return index + list.size();
    }
}
template<typename T>
std::vector<T> inline slice(std::vector<T> list, int start=0, int end=-1, int step=1) {
    vector<T> result;
    start = negative_index_convert(list, start);
    end = negative_index_convert(list, end);
    for(int i = start; i < end; i += step) {
        T element = list[i];
        result.push_back(element);
    }
    return result;
}
/// init a Random Forest  
RandomForest::RandomForest(int n_tree, int n_fearture){
    this->n_trees = n_tree;
    this->n_features = n_fearture;
    for(int i = 0 ; i<n_tree;i++){
        trees.push_back(CARTreeNode());
    }
}
// Random forest train
////// 120 data for train and select 100 for train actual
////// 30  data for test
void RandomForest::RandomForest_train(matrix & m){
    cout<<"This forest each tree is trained by 100 data from "<<m.n_rows()<<" data"<<endl;
    vector<int> all_columns = range(m.n_columns()-1);
    for(int i=0;i<trees.size();i++){
        CARTreeNode & tree = trees[i];
        random_shuffle(all_columns.begin(), all_columns.end());
        vector<int> subset = slice(all_columns, 0, n_features);
        //for(int i = 0 )
        //// select 100 from 120 data randomly
        vector<int> rows = range(120);
        random_shuffle(rows.begin(), rows.end());
        rows.resize(100);
        vector<int> training_cols = range(m.n_columns());
        matrix training = m.submatrix(rows, training_cols);

		//tree.CART_train(training, subset);
        tree.CART_train(training, all_columns);
    }
}

int RandomForest::RF_classify(vector<double> & row){
    int class_number[3]={0};
	for(int i = 0; i < n_trees; i++) {
		CARTreeNode & tree = trees[i];
        double max_possibility = 0;
        int max_index = 50;
		vector<double> distribution = tree.CART_classify(row);
        for(int i = 0 ; i<distribution.size();i++){
            if(distribution[i]>max_possibility){
                max_index = i;
                max_possibility = distribution[i];
            }
        }
        class_number[max_index]++;
    }
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