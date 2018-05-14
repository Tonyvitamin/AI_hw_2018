#include <iostream>
#include <string>
#include <vector>
#include <deque>

int numType;
int type_num;

class TreeNode{
public:
    TreeNode();
    TreeNode();
    void dump(string indent);
    int count();
    void train();
    void train_gini();
    void split_node();
private:
    TreeNode * left;
    TreeNode * right;
    int column;
    double value;
    double gain;
    vector<double> distribution;
};