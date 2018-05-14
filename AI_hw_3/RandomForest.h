#include "CART.h"

class Forest{
public:
    Forest();
    Forest(int n_trees, int n_features);
    void init()
protected:
    int n_trees;
    int n_features;
    deque<TreeNode> trees;    
};