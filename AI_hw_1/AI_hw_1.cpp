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
struct node_bfs{
    int xpos;
    int ypos;
    int movement;
    int depth;
    int dir;
    struct node_bfs * last;
};
struct node_A {
    int xpos;
    int ypos;
    int depth;
    int dir;
    int f;
    int g;
    int h;
    struct node_A *last;
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
    bool operator()(node_A* n1, node_A* n2){
        return n1->f > n2->f;
    }
};
void BFS(deque<int> steps, int x, int y){
    // create deque for bfs and enter the root
    deque<node_bfs *> bfs;
    deque<node_bfs *> record;
    struct node_bfs* start = new node_bfs();
    start->xpos = 0;
    start->ypos = 0;
    start->movement = 0;
    start->depth = 0;
    start->dir = START;
    start->last = start;
    bfs.push_back(start);
    record.push_back(start);
    int node_numbers = 0;
    int depth = 0;

    cout<<"BFS Search starts :\n target is ("<<x<<", "<<y<<")"<<endl;
    int judge = 0;

    while(!steps.empty()){
        int cur_x , cur_y;
        int next_step = steps.front();
        steps.pop_front();
        
        // create a temp deque to catch nodes with the same depth
        deque<node_bfs *> temp_node;

        //cout<<"Current step is "<<next_step<<endl;
        while(!bfs.empty()){
            
            // +x
            node_numbers++; 
            struct node_bfs * xplus = new node_bfs();
            xplus->xpos = bfs.front()->xpos + next_step;
            xplus->ypos = bfs.front()->ypos;
            xplus->movement = next_step;
            xplus->depth = depth + 1;
            xplus->dir = XPLUS;
            xplus->last = bfs.front();
            temp_node.push_back(xplus);
            record.push_back(xplus);
            //cout<<"after +x "<< cur_x << " "<<cur_y<<endl;
            if(x==xplus->xpos && y==xplus->ypos){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                judge = 1;
                break;
            }
            //+y
            node_numbers++;
            struct node_bfs * yplus = new node_bfs();
            yplus->xpos = bfs.front()->xpos;
            yplus->ypos = bfs.front()->ypos + next_step;
            yplus->movement = next_step;
            yplus->depth = depth + 1;
            yplus->dir = YPLUS;
            yplus->last = bfs.front();
            temp_node.push_back(yplus);
            record.push_back(yplus);
            //cout<<"after +x "<< cur_x << " "<<cur_y<<endl;
            if(x==yplus->xpos && y==yplus->ypos){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                judge = 1;
                break;
            }

            //-x
            node_numbers++;
            struct node_bfs * xminus = new node_bfs();
            xminus->xpos = bfs.front()->xpos - next_step;
            xminus->ypos = bfs.front()->ypos;
            xminus->movement = next_step;
            xminus->depth = depth + 1;
            xminus->dir = XMINUS;
            xminus->last = bfs.front();
            temp_node.push_back(xminus);
            record.push_back(xminus);
            //cout<<"after +x "<< cur_x << " "<<cur_y<<endl;
            if(x==xminus->xpos && y==xminus->ypos){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                judge = 1;
                break;
            }
            //-y
            node_numbers++;
            struct node_bfs * yminus = new node_bfs();
            yminus->xpos = bfs.front()->xpos;
            yminus->ypos = bfs.front()->ypos - next_step;
            yminus->movement = next_step;
            yminus->depth = depth + 1;
            yminus->dir = YMINUS;
            yminus->last = bfs.front();
            temp_node.push_back(yminus);
            record.push_back(yminus);
            //cout<<"after +x "<< cur_x << " "<<cur_y<<endl;
            if(x==yminus->xpos && y==yminus->ypos){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                judge = 1;
                break;
            }
            //skip
            node_numbers++;
            struct node_bfs * skip = new node_bfs();
            skip->xpos = bfs.front()->xpos;
            skip->ypos = bfs.front()->ypos;
            skip->movement = next_step;
            skip->depth = depth + 1;
            skip->dir = SKIP;
            skip->last = bfs.front();
            temp_node.push_back(skip);
            record.push_back(skip);
            //cout<<"after +x "<< cur_x << " "<<cur_y<<endl;
            if(x==yminus->xpos && y==yminus->ypos){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                judge = 1;
                break;
            }
            bfs.pop_front();
        }
        // put all node into the real deque 
        if(judge == 0){
            while(!temp_node.empty()){
                bfs.push_back(temp_node.front());
                temp_node.pop_front();
            }
        }
        else {
            struct node_bfs * cur_node = record[node_numbers];
            deque<node_bfs * > path;
            path.push_front(cur_node);
            while(cur_node->last != cur_node){
                cur_node = cur_node->last;
                path.push_front(cur_node);
            }
            while(!path.empty()){
                cout<<path.front()->xpos<<" "<<path.front()->ypos<<endl;
                path.pop_front();
            }
            return;
        }
        depth++;
    }
}
int DFS(deque<int>steps, int x, int y, vector<node_ids> &cur_node, int depth_limit){
    struct node_ids top = cur_node.back();
    if(top.xpos == x && top.ypos == y){
        cout<<"Reach the destination ("<<top.xpos<<", "<<top.ypos<<")"<<endl;
        return 1;
    }
    if(top.depth == depth_limit){
        //cout<<"After move "<<top.movement<<" in the direction "<<top.this_move_dir<<", reach depth limit "<<depth_limit<<" at ("<<top.xpos<<", "<<top.ypos<<")"<<endl;
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
    cout<<"IDS Search starts :\n target is ("<<x<<","<<y<<")"<<endl;

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
        //cout<<"Current start depth is "<<i<<endl;
        //cout<<"Current start node is ("<<topx<<", "<<topy<<")"<<endl;
        //cout<<"Current start step is "<<top_depth<<endl;

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

    int depth = steps.size();
    cout<<"A* Search starts :\n target is ("<<x<<","<<y<<")"<<endl;
    priority_queue<node_A*, vector<node_A*>, f_function> p_queue;
    deque<node_A *> record;
    int start_f = heuristic(0, 0);
    struct node_A  *first = new node_A();
    first->xpos = 0;
    first->ypos = 0;
    first->f = 0 + start_f;
    first->g = 0;
    first->h = start_f;
    first->depth = 0;
    first->dir = START;
    first->last = first;

    p_queue.push(first);
    record.push_back(first);
    int i = 0;
    while(!p_queue.empty()){
        struct node_A *cur_node = p_queue.top();
        record.push_back(cur_node);
        int depth = cur_node->depth;
        int cur_step = steps[depth];

        if(cur_node->xpos == x && cur_node->ypos== y){
            cout<<"target address ("<<x<<", "<<y<<")"<<"found"<<endl;
            break;
        }
        /// +x
        struct node_A* x_plus = new node_A();
        x_plus->xpos = cur_node->xpos + cur_step;
        x_plus->ypos = cur_node->ypos;
        int x_plus_heu = heuristic(x_plus->xpos , x_plus->ypos);
        x_plus->f = depth+1 + x_plus_heu;
        x_plus->g = depth+1;
        x_plus->h = x_plus_heu;
        x_plus->depth = depth+1;
        x_plus->dir = XPLUS;
        x_plus->last = cur_node;
        p_queue.push(x_plus);

        // +y
        struct node_A* y_plus = new node_A();
        y_plus->xpos = cur_node->xpos;
        y_plus->ypos = cur_node->ypos + cur_step;
        int y_plus_heu = heuristic(y_plus->xpos , y_plus->ypos);
        y_plus->f = depth+1 + y_plus_heu;
        y_plus->g = depth+1;
        y_plus->h = y_plus_heu;
        y_plus->depth = depth+1;
        y_plus->dir = YPLUS;
        y_plus->last = cur_node;
        p_queue.push(y_plus);

        // -x
        struct node_A* x_minus = new node_A();
        x_minus->xpos = cur_node->xpos - cur_step;
        x_minus->ypos = cur_node->ypos;
        int x_minus_heu = heuristic(x_minus->xpos , x_minus->ypos);
        x_minus->f = depth+1 + x_minus_heu;
        x_minus->g = depth+1;
        x_minus->h = x_minus_heu;
        x_minus->depth = depth+1;
        x_minus->dir = XMINUS;
        x_minus->last = cur_node;
        p_queue.push(x_minus);

        // -y
        struct node_A* y_minus = new node_A();
        y_minus->xpos = cur_node->xpos;
        y_minus->ypos = cur_node->ypos - cur_step;
        int y_minus_heu = heuristic(y_minus->xpos , y_minus->ypos);
        y_minus->f = depth+1 + y_minus_heu;
        y_minus->g = depth+1;
        y_minus->h = y_minus_heu;
        y_minus->depth = depth+1;
        y_minus->dir = YMINUS;
        y_minus->last = cur_node;
        p_queue.push(y_minus);

        // skip
        struct node_A* skip = new node_A();
        skip->xpos = cur_node->xpos;
        skip->ypos = cur_node->ypos;
        int skip_heu = heuristic(skip->xpos , skip->ypos);
        skip->f = depth+1 + skip_heu;
        skip->g = depth+1;
        skip->h = skip_heu;
        skip->depth = depth+1;
        skip->dir = SKIP;
        skip->last = cur_node;
        p_queue.push(skip);
        
        p_queue.pop();
    }
    struct node_A * temp = record.back();
    deque<node_A*> path;
    path.push_back(temp);
    while(temp->last != temp){
        temp = temp->last;
        path.push_front(temp);
    }
    while(!path.empty()){
        cout<<path.front()->xpos<<" "<<path.front()->ypos<<" at depth "<<path.front()->depth<<endl;
        path.pop_front();
   }
}



int main(){
    fstream file("IntroAI_PR1_test.txt"); 
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
        cout<<"Time cost is "<<time_used<<" sec"<<endl<<endl;
    }
}
