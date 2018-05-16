

#include <vector>

#include "CART.hpp"

class RandomForest{
public:
    RandomForest();
    RandomForest(int n_trees, int n_features);
    void init();
    void RandomForest_train(matrix & m);
    //vector<double> RF_classify(vector<double> &row);
    int RF_classify(vector<double> &row);

protected:
    int n_trees;
    int n_features;
    vector<CARTreeNode> trees;    
};