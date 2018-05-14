#include <vector> 
#include <deque>

using namespace std;

class matrix{

private:
	vector<vector<double> > elements;
	vector<string> column_labels;
	vector<string> class_label;
public:
    void load(string filename);
	void save(string filename);
	int n_columns();
	int n_rows();
	vector<double> column(int index);
	matrix submatrix(vector<int> rows, vector<int> columns);
	void split(int column_index, double value, matrix & m1, matrix & m2);
	matrix shuffled();
	//void append_column(vector<double> & col, string name="");
	//void merge_rows(matrix & other);
	//Bracket overloaded operator:
	vector<double> & operator[](int i);
};