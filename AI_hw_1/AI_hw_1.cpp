#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <cmath>
#include <string>
#include <sys/time.h>


using namespace std;
enum dir_type {START, XPLUS, YPLUS, XMINUS, YMINUS, SKIP};

/// external declaration is used for to count the current node expansion in IDS
int cost = 1;
////external declaration is convient for heuristc computation
float x, y;
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
    int movement;
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
    ////////// start BFS ///////////
    struct timeval tstart , tend , diff;
    double time_used;
    gettimeofday(&tstart, NULL);
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
    cout<<endl;
    cout<<"BFS Search starts :\ntarget is ("<<x<<", "<<y<<")"<<endl;
    int judge = 0;
    while(!steps.empty()){
        int cur_x , cur_y;
        int next_step = steps.front();
        steps.pop_front();
        // create a temp deque to catch nodes with the same depth
        deque<node_bfs *> temp_node;
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
            if(x==xplus->xpos && y==xplus->ypos){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                gettimeofday(&tend, NULL);
                timersub(&tend, &tstart, &diff);
                time_used = diff.tv_sec + (double) diff.tv_usec / 1000000.0;
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
            if(x==yplus->xpos && y==yplus->ypos){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                gettimeofday(&tend, NULL);
                timersub(&tend, &tstart, &diff);
                time_used = diff.tv_sec + (double) diff.tv_usec / 1000000.0;
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
            if(x==xminus->xpos && y==xminus->ypos){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                gettimeofday(&tend, NULL);
                timersub(&tend, &tstart, &diff);
                time_used = diff.tv_sec + (double) diff.tv_usec / 1000000.0;
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
            if(x==yminus->xpos && y==yminus->ypos){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                gettimeofday(&tend, NULL);
                timersub(&tend, &tstart, &diff);
                time_used = diff.tv_sec + (double) diff.tv_usec / 1000000.0;
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
            if(x==yminus->xpos && y==yminus->ypos){
                cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
                gettimeofday(&tend, NULL);
                timersub(&tend, &tstart, &diff);
                time_used = diff.tv_sec + (double) diff.tv_usec / 1000000.0;
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
            cout<<"The path which BFS found :"<<endl;
            cout<<"initial "<<"     ("<<path.front()->xpos<<", "<<path.front()->ypos<<")"<<endl;
            path.pop_front();
            while(!path.empty()){
                cout<<"(";
                if(path.front()->dir == XPLUS)
                    cout<<"x+";
                else if (path.front()->dir == YPLUS)
                    cout<<"y+";
                else if (path.front()->dir == XMINUS)
                    cout<<"x-";
                else if(path.front()->dir == YMINUS)
                    cout<<"y-";
                else 
                    cout<<"S";
                cout<<") "<<path.front()->movement<<"   ";

                cout<<"("<<path.front()->xpos<<", "<<path.front()->ypos<<")"<<endl;
                path.pop_front();
            }
            cout<<"BFS costs "<<node_numbers+1<<" node expansion"<<endl;
            cout<<"Time cost is "<<time_used<<" sec"<<endl<<endl;
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
    cost++;
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
    cost++;
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
    cost++;
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
    cost++;
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
    cost++;
    if(judge==1){
        return judge;
    }
    cur_node.pop_back();

    return judge;
}
void IDS(deque<int>steps, int x, int y){
    int depth = steps.size();
    vector<node_ids> ids;
    cout<<"IDS Search starts :\ntarget is ("<<x<<","<<y<<")"<<endl;
    ////// start IDS ///////////
    struct timeval tstart , tend , diff;
    double time_used;
    gettimeofday(&tstart, NULL);
    for(int i = 0 ; i<depth ; i++){
        struct node_ids first ;
        first.xpos = 0;
        first.ypos = 0;
        first.depth = 0;
        first.movement = 0;
        first.this_move_dir = 0;
        ids.push_back(first);
        //// look for the right path by DFS 
        int judge = DFS(steps, x, y, ids, i);
        if(judge == 1){
            gettimeofday(&tend, NULL);
            timersub(&tend, &tstart, &diff);
            time_used = diff.tv_sec + (double) diff.tv_usec / 1000000.0;
            break;
        }
        ids.clear();
        cost = 1;
    }

    //// print the result 
    cout<<"The path IDS found :"<<endl;
    cout<<"initial     ("<<ids[0].xpos<<", "<<ids[0].ypos<<")"<<endl;
    for(int i = 1 ; i < ids.size() ; i++ ){
        struct node_ids temp = ids[i];
        cout<<"(";
        if(temp.this_move_dir == XPLUS)
            cout<<"x+";
        else if(temp.this_move_dir == YPLUS)
            cout<<"y+";
        else if(temp.this_move_dir == XMINUS)
            cout<<"x-";
        else if(temp.this_move_dir == YMINUS)
            cout<<"y-";
        else 
            cout<<"S";
        cout<<")   "<<temp.movement<<"     (";
        cout<<temp.xpos<<", "<<temp.ypos<<")"<<endl;
    }
    cout<<"IDS costs "<<cost<<" node expansion"<<endl;
    cout<<"Time cost is "<<time_used<<" sec"<<endl<<endl;
    cost = 0;
}
int heuristic(float posx, float posy){
    int dx = floor((abs(posx-x))/9);
    int dy = floor((abs(posy-y))/9);
    return dx+dy;
}
void A_search(deque<int>steps, int x, int y){
    cout<<endl;
    cout<<"A* Search starts :\ntarget is ("<<x<<","<<y<<")"<<endl;
    int cost = 1;
    priority_queue<node_A*, vector<node_A*>, f_function> p_queue;
    deque<node_A *> record;
    
    ////////// start A * search ////////
    struct timeval tstart , tend , diff;
    double time_used;
    gettimeofday(&tstart, NULL);

    // push root into p_queue and record
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
    first->movement = 0;
    p_queue.push(first);
    record.push_back(first);

    // A* search starts here 
    while(!p_queue.empty()){
        struct node_A *cur_node = p_queue.top();
        p_queue.pop();
        record.push_back(cur_node);
        int depth = cur_node->depth;
        int cur_step = steps[depth];

        if(cur_node->xpos == x && cur_node->ypos== y){
            cout<<"Reach the destination ("<<x<<", "<<y<<")"<<endl;
            /////////// stop A * search /////////
            gettimeofday(&tend, NULL);
            timersub(&tend, &tstart, &diff);
            time_used = diff.tv_sec + (double) diff.tv_usec / 1000000.0;
            break;
        }

        /// push +x node 
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
        x_plus->movement = cur_step;
        p_queue.push(x_plus);
        cost++;

        // push +y node
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
        y_plus->movement = cur_step;
        p_queue.push(y_plus);
        cost++;

        // push -x node
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
        x_minus->movement = cur_step;
        p_queue.push(x_minus);
        cost++;

        // push -y node
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
        y_minus->movement = cur_step;
        p_queue.push(y_minus);
        cost++;

        // push skip node
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
        skip->movement = cur_step;
        p_queue.push(skip);
        cost++;
        
    }

    // print out result 
    struct node_A * temp = record.back();
    deque<node_A*> path;
    path.push_back(temp);
    while(temp->last != temp){
        temp = temp->last;
        path.push_front(temp);
    }
    cout<<"The path which A* search found :"<<endl;
    cout<<"initial "<<"     ("<<path.front()->xpos<<", "<<path.front()->ypos<<")"<<endl;
    path.pop_front();
    while(!path.empty()){
        cout<<"(";
        if(path.front()->dir == XPLUS)
            cout<<"x+";
        else if (path.front()->dir == YPLUS)
            cout<<"y+";
        else if (path.front()->dir == XMINUS)
            cout<<"x-";
        else if(path.front()->dir == YMINUS)
            cout<<"y-";
        else 
            cout<<"S";
        cout<<") "<<path.front()->movement<<"   ";
        cout<<"("<<path.front()->xpos<<", "<<path.front()->ypos<<")"<<endl;
        path.pop_front();
    }

    cout<<endl<<"A* search costs "<<cost<<" node expansion"<<endl;
    cout<<"Time cost is "<<time_used<<" sec"<<endl<<endl;
    return;
}
int main(){
    fstream file("IntroAI_PR1_test.txt"); 
    string search;
    string str;

    ////// read the file /////////
    while(getline(file , str)){
        stringstream ss(str);
        ss>>search;
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
    //////// choose the correponding method to search /////////
        if(search == "BFS")
            BFS(steps, x, y);
        else if(search == "IDS")
            IDS(steps, x, y);
        else if(search == "A*")
            A_search(steps, x, y);
    }
}
