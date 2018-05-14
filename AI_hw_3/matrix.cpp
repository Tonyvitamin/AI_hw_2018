#include "matrix.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib> 
#include <string>
#include <vector>

using namespace std;

// load the data into the matrix
void matrix::load(string filename){
    fstream f_input(filename.c_str());
    int lineNumber = 0;
    int attrNumber = 0;
    string line;
    while(getline(f_input, line)){
        istringstream ss(line);
        vector<string> temp;
        vector<double> row;
        string word;

        while(getline(ss,word,',')){
            temp.push_back(word);
            word.clear();
        }

        class_label.push_back(temp[temp.size()-1]); // push class name into class_label
        attrNumber = temp.size()-1;
        for(int i = 0 ; i < temp.size()-1 ; i++){ // all attributes of an object
            double value = atof(temp[i].c_str());
            row.push_back(value);
        }
        elements.push_back(row);
        lineNumber++;
    }
    cout<<lineNumber<<" rows of object and "<<attrNumber<<" attributes"<<endl;
    f_input.close();
}
// return the number of column
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
    for(int i = 0; i<elements.size();i++){
        col.push_back(elements[i][index]);
    }
    return col;
}

matrix matrix::submatrix(vector<int> rows, vector<int> cols){
    matrix m;	
    for(int i = 0; i < rows.size(); i++) {
		int y = rows[i];
		vector<double> row;

		for(int j = 0; j < columns.size(); j++) {
			int x = columns[j];
			row.push_back(elements[y][x]);
		}
		m.elements.push_back(row);
	}
	return m;
}
