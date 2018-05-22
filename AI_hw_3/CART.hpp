#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>

#include "matrix.hpp"

using namespace std;
// Decision tree based on CART
class CARTreeNode{
public:
    CARTreeNode();
    ~CARTreeNode();
    void CART_train(matrix &m , vector<int> attributes);
    void train_gini();
    void split_node();
    vector<double> CART_classify(vector<double> &row);
private:
    CARTreeNode * left;
    CARTreeNode * right;
    int attribute;
    double threshold_value;
    double gain;
    vector<double> distribution;
};