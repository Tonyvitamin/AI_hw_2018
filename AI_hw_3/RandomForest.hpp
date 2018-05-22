

#include <vector>

#include "CART.hpp"
// Random Forest structure
class RandomForest{
public:
    RandomForest(int n_trees, int n_features);
    void RandomForest_train(matrix & m);
    int RF_classify(vector<double> &row);

protected:
    int n_trees;
    int n_features;
    vector<CARTreeNode> trees;    
};