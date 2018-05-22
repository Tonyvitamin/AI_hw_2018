#include "matrix.hpp"
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <map>
#include <iostream>
#include <cstdlib> 
#include <string>
#include <vector>

using namespace std;
vector<int> range(int num){
    vector<int> v;
    for(int i = 0 ; i<num;i++){
        v.push_back(i);
    }
    return v;
}

// load the data into the matrix
// set "iris.txt" for the convenient of reading the input data
void matrix::load(string filename){
    FILE * f_input;
    f_input = fopen(filename.c_str(), "r");
    int lineNumber = 0;
    int attrNumber = 0;
    string line;
    double v1, v2, v3, v4;
    char  word[80];
    /// iris.txt input format
    while(fscanf(f_input, "%lf,%lf,%lf,%lf,%s", &v1,&v2,&v3,&v4,word)!=EOF){
        vector<double> row;
        row.push_back(v1);
        row.push_back(v2);
        row.push_back(v3);
        row.push_back(v4);
        if(strcmp(word, "Iris-setosa")==0)
            row.push_back(0);
        else if(strcmp(word, "Iris-versicolor")==0)
            row.push_back(1);
        else if(strcmp(word, "Iris-virginica")==0)
            row.push_back(2);
        elements.push_back(row);
        lineNumber++;
    }
    cout<<lineNumber<<" rows of object and "<<4<<" attributes"<<endl;

    // print each row of data
    /*for(int i = 0 ;i < elements.size();i++){
        int j;
        for(j = 0 ; j< elements[0].size()-1;j++){
            cout<<elements[i][j]<<" ";
        }
        cout<<elements[i][j]<<endl;
    }*/

    fclose(f_input);
}
// return the number of column(including class label)
int matrix::n_columns(){
    return elements[0].size();
}
// return the number of row
int matrix::n_rows(){
    return elements.size();
}
// return all data of a specific attribute 
vector<double> matrix::column(int index){
    vector<double> col;
    if(index<0)
        index += n_columns();
    for(int i = 0; i<elements.size();i++){
        col.push_back(elements[i][index]);
    }
    return col;
}
// return a submatrix given to the row index and column index
matrix matrix::submatrix(vector<int> rows, vector<int> cols){
    matrix m;	
    for(int i = 0; i < rows.size(); i++) {
		int y = rows[i];
		vector<double> row;
		for(int j = 0; j < cols.size(); j++) {
			int x = cols[j];
			row.push_back(elements[y][x]);
		}
		m.elements.push_back(row);
	}
	return m;
}
// shuffle function to get random training data or attribute
matrix matrix::shuffled(){
	vector<int> row_indices = range(n_rows());
	random_shuffle(row_indices.begin(), row_indices.end());
	vector<int> column_indices = range(n_columns());
	return submatrix(row_indices, column_indices);
}

// split a matrix into two part (left and right)
void matrix::split(int column_index, double value, matrix &l, matrix&r){
	vector<int> l_rows;
	vector<int> r_rows;
	for(int i = 0; i < elements.size(); i++) {
		double element = elements[i][column_index];
		if(element <= value) {
			l_rows.push_back(i);
		}
		else {
			r_rows.push_back(i);
		}
	}
	vector<int> all_cols = range(n_columns());
	l = submatrix(l_rows, all_cols);
	r = submatrix(r_rows, all_cols);
}