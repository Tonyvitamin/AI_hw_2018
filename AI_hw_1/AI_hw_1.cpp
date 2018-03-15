#include <iostream>
#include <fstream>
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
    while(file>>search){
        cout<<search<<endl;
        int x , y;
        file>>x;
        file>>y;
        cout<<x<<" "<<y<<" "<<endl;
        int step;
        vector <int> steps ;
        while(file>>step){
            cout<<step<<" ";
            steps.push_back(step);
        }
        
        cout<<endl;
        
    }

}