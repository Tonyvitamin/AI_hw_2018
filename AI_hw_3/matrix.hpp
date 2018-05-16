#include <vector> 
#include <deque>

using namespace std;

class matrix{



public:
    void load(string filename);
	void save(string filename);
	int n_columns();
	int n_rows();
	vector<double> column(int index);
	matrix submatrix(vector<int> rows, vector<int> columns);
	void split(int column_index, double value, matrix & l, matrix & r);
	matrix shuffled();
	//void merge_rows(matrix & other);
	//Bracket overloaded operator:
	vector<double> & operator[](int i);
	vector<vector<double> > elements;
};
vector<int> range(int num);
vector<int> cluster_transfer(vector<string> &class_label);
