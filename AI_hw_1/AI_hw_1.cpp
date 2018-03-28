#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <cmath>
#include <map>
#include <string>
#include <sys/time.h>


enum dir_type {START, XPLUS, YPLUS, XMINUS, YMINUS, SKIP};

using namespace std;
float x , y;
struct node {
    int xpos;
    int ypos;
    int depth;
    int f;
    int g;
    int h;
};
struct node_ids{
    int xpos;
    int ypos;
    int depth;
    int movement;
    int this_move_dir;
};
class f_function{
public:
    bool operator()(node n1, node n2){
        return n1.f > n2.f;
    }
};
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
            //cout<<"after +x "<< cur_x << " "<<cur_y<<endl;
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
            //cout<<"after +y "<< cur_x << " "<<cur_y<<endl;
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
            //cout<<"after -x "<< cur_x << " "<<cur_y<<endl;
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
            //cout<<"after -y "<< cur_x << " "<<cur_y<<endl;
            if(x==cur_x && y==cur_y){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                return;
            }
            //skip
            node_numbers++;
            tempx.push_back(xpos.front());
            tempy.push_back(ypos.front());
            //cout<<"after skip "<< xpos.front() << " "<<ypos.front()<<endl;
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
int DFS(deque<int>steps, int x, int y, vector<node_ids> &cur_node, int depth_limit){
    struct node_ids top = cur_node.back();
    if(top.xpos == x && top.ypos == y){
        cout<<"Reach the destination ("<<top.xpos<<", "<<top.ypos<<")"<<endl;
        return 1;
    }
    if(top.depth == depth_limit){
        cout<<"After move "<<top.movement<<" in the direction "<<top.this_move_dir<<", reach depth limit "<<depth_limit<<" at ("<<top.xpos<<", "<<top.ypos<<")"<<endl;
        return 0;
    }

    struct node_ids xplus, yplus, xminus, yminus, skip;
    int judge = 0;
    xplus.xpos = top.xpos + steps[top.depth];
    xplus.ypos = top.ypos;
    xplus.depth = top.depth + 1;
    xplus.movement = steps[top.depth];
    xplus.this_move_dir = XPLUS;
    cur_node.push_back(xplus);
    judge = DFS(steps, x, y, cur_node, depth_limit);
    if(judge==1){
        return judge;
    }
    cur_node.pop_back();

    yplus.xpos = top.xpos;
    yplus.ypos = top.ypos + steps[top.depth];
    yplus.depth = top.depth + 1;
    yplus.movement = steps[top.depth];
    yplus.this_move_dir = YPLUS;
    cur_node.push_back(yplus);
    judge = DFS(steps, x, y, cur_node, depth_limit);
    if(judge==1){
        return judge;
    }
    cur_node.pop_back();

    xminus.xpos = top.xpos - steps[top.depth];
    xminus.ypos = top.ypos;
    xminus.depth = top.depth + 1;
    xminus.movement = steps[top.depth];
    xminus.this_move_dir = XMINUS;
    cur_node.push_back(xminus);
    judge = DFS(steps, x, y, cur_node, depth_limit);
    if(judge==1){
        return judge;
    }
    cur_node.pop_back();

    yminus.xpos = top.xpos;
    yminus.ypos = top.ypos - steps[top.depth];
    yminus.depth = top.depth + 1;
    yminus.movement = steps[top.depth];
    yminus.this_move_dir = YMINUS;
    cur_node.push_back(yminus);
    judge = DFS(steps, x, y, cur_node, depth_limit);
    if(judge==1){
        return judge;
    }
    cur_node.pop_back();

    skip.xpos = top.xpos;
    skip.ypos = top.ypos;
    skip.depth = top.depth + 1;
    skip.movement = steps[top.depth];
    skip.this_move_dir = SKIP;
    cur_node.push_back(skip);
    judge = DFS(steps, x, y, cur_node, depth_limit);
    if(judge==1){
        return judge;
    }
    cur_node.pop_back();

    return judge;
}
void IDS(deque<int>steps, int x, int y){
    int depth = steps.size();
    vector<node_ids> ids;
    cout<<"IDS search start :\n target is ("<<x<<","<<y<<") with depth "<<depth<<endl;

    for(int i = 0 ; i<depth ; i++){
        struct node_ids first ;
        first.xpos = 0;
        first.ypos = 0;
        first.depth = 0;
        first.movement = 0;
        first.this_move_dir = 0;
        ids.push_back(first);
        struct node_ids top;
        top = ids.back();
        int topx = top.xpos;
        int topy = top.ypos;
        int top_depth = top.depth;
        cout<<"Current start depth is "<<i<<endl;
        cout<<"Current start node is ("<<topx<<", "<<topy<<")"<<endl;
        cout<<"Current start step is "<<top_depth<<endl;

        int judge = DFS(steps, x, y, ids, i);
        if(judge == 1){
            break;
        }
        ids.clear();
    }
    for(int i = 0 ; i < ids.size() ; i++ ){
        struct node_ids temp = ids[i];
        cout<<"direction is "<<temp.this_move_dir<<" move "<<temp.movement<<" ("<<temp.xpos<<", "<<temp.ypos<<")"<<endl;
    }
}
int heuristic(float posx, float posy){
    int dx = floor((abs(posx-x))/9);
    
    int dy = floor((abs(posy-y))/9);
    //cout<<(abs(posx-x))/9<<" "<<(abs(posy-y))/9;
    return dx+dy;
}
void A_search(deque<int>steps, int x, int y){
    priority_queue<node, vector<node>, f_function> p_queue;

    int start_f = heuristic(0, 0);
    struct node  first ;
    first.xpos = 0;
    first.ypos = 0;
    first.f = 0 + start_f;
    first.g = 0;
    first.h = start_f;
    first.depth = 0;
    p_queue.push(first);

    int i = 0;
    while(!p_queue.empty()){
        //out<<"here"<<endl;
        struct node cur = p_queue.top();
        int depth = cur.depth;
        int cur_step = steps[depth];

        if(cur.xpos == x && cur.ypos== y){
            cout<<"target address ("<<x<<", "<<y<<")"<<"found"<<endl;
            return;
        }
        /// +x
        struct node x_plus;
        x_plus.xpos = cur.xpos + cur_step;
        x_plus.ypos = cur.ypos;
        int x_plus_heu = heuristic(x_plus.xpos , x_plus.ypos);
        x_plus.f = depth+1 + x_plus_heu;
        x_plus.g = depth+1;
        x_plus.h = x_plus_heu;
        x_plus.depth = depth+1;
        p_queue.push(x_plus);

        // +y
        struct node y_plus;
        y_plus.xpos = cur.xpos;
        y_plus.ypos = cur.ypos + cur_step;
        int y_plus_heu = heuristic(y_plus.xpos , y_plus.ypos);
        y_plus.f = depth+1 + y_plus_heu;
        y_plus.g = depth+1;
        y_plus.h = y_plus_heu;
        y_plus.depth = depth+1;
        p_queue.push(y_plus);

        // -x
        struct node x_minus;
        x_minus.xpos = cur.xpos - cur_step;
        x_minus.ypos = cur.ypos;
        int x_minus_heu = heuristic(x_minus.xpos , x_minus.ypos);
        x_minus.f = depth+1 + x_minus_heu;
        x_minus.g = depth+1;
        x_minus.h = x_minus_heu;
        x_minus.depth = depth+1;
        p_queue.push(x_minus);

        // -y
        struct node y_minus;
        y_minus.xpos = cur.xpos;
        y_minus.ypos = cur.ypos - cur_step;
        int y_minus_heu = heuristic(y_minus.xpos , y_minus.ypos);
        y_minus.f = depth+1 + y_minus_heu;
        y_minus.g = depth+1;
        y_minus.h = y_minus_heu;
        y_minus.depth = depth+1;
        p_queue.push(y_minus);

        // skip
        struct node skip;
        skip.xpos = cur.xpos;
        skip.ypos = cur.ypos;
        int skip_heu = heuristic(skip.xpos , skip.ypos);
        skip.f = depth+1 + skip_heu;
        skip.g = depth+1;
        skip.h = skip_heu;
        skip.depth = depth+1;
        p_queue.push(skip);
        
        p_queue.pop();
    }
}



int main(){
    fstream file("IntroAI_PR1_test1.txt"); 
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
        cout<<"Time cost is "<<time_used<<" sec"<<endl;

    }

}
