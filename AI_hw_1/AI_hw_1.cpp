#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <string>


using namespace std;


void BFS(deque<int> steps, int x, int y){
    deque<int> xpos;
    deque<int> ypos;
    xpos.push_back(0);
    ypos.push_back(0);
    while(!steps.empty()){
        int cur_x , cur_y;
        int next_step = steps.front();
        steps.pop_front();
        deque<int> tempx , tempy;
        cout<<next_step<<endl;
        while(!xpos.empty()){
            // +x 
            cur_x = xpos.front() + next_step;
            cur_y = ypos.front();
            tempx.push_back(cur_x);
            tempy.push_back(cur_y);
            cout<<"after +x "<< cur_x << " "<<cur_y<<endl;
            //cout<<"after +x "<< xpos.back() << " "<<ypos.back()<<endl;
            if(x==cur_x && y==cur_y)
                return;
            //+y
            cur_x = xpos.front();
            cur_y = ypos.front() + next_step;
            tempx.push_back(cur_x);
            tempy.push_back(cur_y);
            cout<<"after +y "<< cur_x << " "<<cur_y<<endl;
            if(x==cur_x && y==cur_y)
                return;     
            //-x
            cur_x = xpos.front() - next_step;
            cur_y = ypos.front();
            tempx.push_back(cur_x);
            tempy.push_back(cur_y);
            cout<<"after -x "<< cur_x << " "<<cur_y<<endl;
            if(x==cur_x && y==cur_y)
                return; 
            //-y
            cur_x = xpos.front();
            cur_y = ypos.front() - next_step;
            tempx.push_back(cur_x);
            tempy.push_back(cur_y);
            cout<<"after -y "<< cur_x << " "<<cur_y<<endl;
            if(x==cur_x && y==cur_y)
                return;
            //skip
            tempx.push_back(xpos.front());
            tempy.push_back(ypos.front());
            cout<<"after skip "<< xpos.back() << " "<<ypos.back()<<endl;
            if(x==cur_x && y==cur_y)
                return;
            xpos.pop_front();
            ypos.pop_front();
        }
        while(!tempx.empty()){
            xpos.push_back(tempx.front());
            ypos.push_back(tempy.front());
            tempx.pop_front();
            tempy.pop_front();
        }

    }
}
int heuristic(){

}
void IDS(){
    
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

        deque<int> steps;
        while(ss>>temp){
            steps.push_back(temp);
            cout<<temp<<" ";
        }
        if(search == "BFS")
            BFS(steps, x, y);
        //system("pause");
        cout<<endl;

    }

}