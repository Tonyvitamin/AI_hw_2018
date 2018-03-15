#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <string>


using namespace std;


void BFS(int d){
    
}


int main(){
    fstream file("IntroAI_PR1_test.txt"); 
    string search;
    string str;
    while(getline(file , str)){
        stringstream ss(str);
        ss>>search;
        int x , y;
        ss>>x>>y;
        int temp;
        cout<<search<<" ";
        cout<<x<<" "<<y<<" ";

        vector<int> steps;
        while(ss>>temp){
            steps.push_back(temp);
            cout<<temp<<" ";
        }
        cout<<endl;

    }

}