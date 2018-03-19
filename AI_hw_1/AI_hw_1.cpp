#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <map>
#include <string>
#include <sys/time.h>

using namespace std;
int x , y;
class f_function{
public:
    bool operator()(pair<int, int> n1, pair<int, int> n2){

    }
};

int heuristic(int posx, int posy){
    int dx = abs((posx-x)/9);
    int dy = abs((posy-y)/9);
    return dx+dy;
}
void A_search(deque<int>steps, int x, int y){
    priority_queue<pair<int, int>, vector<pair<int, int> >, f_function> node;


}
void BFS(deque<int> steps, int x, int y){
    deque<int> xpos, ypos;
    int node_numbers = 0;
    xpos.push_back(0);
    ypos.push_back(0);
    cout<<"BFS search start :\n target is ("<<x<<", "<<y<<")"<<endl;
    while(!steps.empty()){
        int cur_x , cur_y;
        int next_step = steps.front();
        steps.pop_front();
        // create a temp deque to catch nodes with the same depth
        deque<int> tempx , tempy;
        cout<<"next step is "<<next_step<<endl;
        while(!xpos.empty()){
            
            // +x
            node_numbers++; 
            cur_x = xpos.front() + next_step;
            cur_y = ypos.front();
            tempx.push_back(cur_x);
            tempy.push_back(cur_y);
            cout<<"after +x "<< cur_x << " "<<cur_y<<endl;
            if(x==cur_x && y==cur_y){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                return;
            }
            //+y
            node_numbers++;
            cur_x = xpos.front();
            cur_y = ypos.front() + next_step;
            tempx.push_back(cur_x);
            tempy.push_back(cur_y);
            cout<<"after +y "<< cur_x << " "<<cur_y<<endl;
            if(x==cur_x && y==cur_y){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                return;
            }  
            //-x
            node_numbers++;
            cur_x = xpos.front() - next_step;
            cur_y = ypos.front();
            tempx.push_back(cur_x);
            tempy.push_back(cur_y);
            cout<<"after -x "<< cur_x << " "<<cur_y<<endl;
            if(x==cur_x && y==cur_y){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                return;
            }
            //-y
            node_numbers++;
            cur_x = xpos.front();
            cur_y = ypos.front() - next_step;
            tempx.push_back(cur_x);
            tempy.push_back(cur_y);
            cout<<"after -y "<< cur_x << " "<<cur_y<<endl;
            if(x==cur_x && y==cur_y){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                return;
            }
            //skip
            node_numbers++;
            tempx.push_back(xpos.front());
            tempy.push_back(ypos.front());
            cout<<"after skip "<< xpos.front() << " "<<ypos.front()<<endl;
            if(x==cur_x && y==cur_y){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                return;
            }
            xpos.pop_front();
            ypos.pop_front();
        }
        // put all node into the real deque 
        while(!tempx.empty()){
            xpos.push_back(tempx.front());
            ypos.push_back(tempy.front());
            tempx.pop_front();
            tempy.pop_front();
        }

    }
}
void IDS(deque<int>steps, int x, int y){
    int depth = steps.size();
    vector<int> xpos, ypos, node_depth;
    cout<<"IDS search start :\n target is ("<<x<<","<<y<<" ) with depth"<<depth<<endl;

    for(int i = 0 ; i<depth ; i++){
        xpos.push_back(0);
        ypos.push_back(0);
        node_depth.push_back(0);
        while(!xpos.empty()){
            int topx , topy , top_depth;
            topx = xpos.back();
            topy = ypos.back();
            if(topx == x && topy == y){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                return;
            }
            top_depth = node_depth.back();
            cout<<"Current depth is "<<i<<endl;
            cout<<"Current node is ("<<topx<<", "<<topy<<")"<<endl;
            cout<<"Current step is "<<top_depth<<endl;
            xpos.pop_back();
            ypos.pop_back();
            node_depth.pop_back();
            if(top_depth < i){
                //skip
                int cur_x = topx;
                int cur_y = topy;
                xpos.push_back(cur_x);
                ypos.push_back(cur_y);
                node_depth.push_back(top_depth+1);
                //-y
                cur_x = xpos.back();
                cur_y = ypos.back() - steps[top_depth];
                xpos.push_back(cur_x);
                ypos.push_back(cur_y);
                node_depth.push_back(top_depth+1);

                //-x
                cur_x = xpos.back() - steps[top_depth];
                cur_y = ypos.back();
                xpos.push_back(cur_x);
                ypos.push_back(cur_y);
                node_depth.push_back(top_depth+1);

                //+y
                cur_x = xpos.back();
                cur_y = ypos.back() + steps[top_depth];
                xpos.push_back(cur_x);
                ypos.push_back(cur_y);
                node_depth.push_back(top_depth+1);

                //+x
                cur_x = xpos.back() + steps[top_depth];
                cur_y = ypos.back();
                xpos.push_back(cur_x);
                ypos.push_back(cur_y);
                node_depth.push_back(top_depth+1);
            }
        }
            xpos.clear();
            ypos.clear();
            node_depth.clear();
    }


}


int main(){
    fstream file("IntroAI_PR1_test3.txt"); 
    string search;
    string str;
    while(getline(file , str)){
        stringstream ss(str);
        ss>>search;
        //int x , y;
        ss>>x>>y;
        int temp;
        cout<<search<<" ";
        cout<<x<<" "<<y<<" ";

        deque<int> steps;
        while(ss>>temp){
            steps.push_back(temp);
            cout<<temp<<" ";
        }
        cout<<endl;
        struct timeval start , end , diff;
        gettimeofday(&start, NULL);
        if(search == "BFS")
            BFS(steps, x, y);
        else if(search == "IDS")
            IDS(steps, x, y);
        else if(search == "A*")
            A_search(steps, x, y);
        gettimeofday(&end, NULL);
        timersub(&end, &start, &diff);
        double time_used = diff.tv_sec + (double) diff.tv_usec / 1000000.0;
        cout<<"Time cost is "<<time_used<<" sec";

    }

}