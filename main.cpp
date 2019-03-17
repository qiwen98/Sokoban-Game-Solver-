// Astar.cpp

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "tools.h"

#include "map3.h" //Need to manually change the map number to change to different size of map
//Example:map1.h,map2.h,map3.h


//disclaimer
//You can replace all the Sleep(20); to Sleep(20); to make the program do its job automatically without any pressing needed.
//the max number of box is 3



using namespace std;
HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE); //just once



const int n=map_x_Size; // horizontal size of the map
const int m=map_y_Size; // vertical size size of the map
const int boxnumber=boxnumbersetting; //the number of box * the max number is 3
static int map[n][m];
static int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
static int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
static int dir_map[n][m]; // map of directions
const int dir=4; // number of possible directions to go at any position
// if dir==4
static int dx[dir]= {1, 0, -1, 0};
static int dy[dir]= {0, 1, 0, -1};
// if dir==8
//static int dx[dir]= {1, 1, 0, -1, -1, -1, 0, 1};
//static int dy[dir]= {0, 1, 1, 1, 0, -1, -1, -1};


class node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level; //
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority

public:
    node(int xp, int yp, int d, int p)
    {
        xPos=xp;
        yPos=yp;
        level=d;
        priority=p;
    }

    int getxPos() const
    {
        return xPos;
    }
    int getyPos() const
    {
        return yPos;
    }
    int getLevel() const
    {
        return level;
    }
    int getPriority() const
    {
        return priority;
    }

    void updatePriority(const int & xDest, const int & yDest)
    {
        priority=level+estimate(xDest, yDest)*10; //A*
    }

    // give better priority to going strait instead of diagonally
    void nextLevel(const int & i) // i: direction
    {
        level+=(dir==8?(i%2==0?10:14):10);
    }

    // Estimation function for the remaining distance to the goal.
    const int & estimate(const int & xDest, const int & yDest) const
    {
        static int xd, yd, d;
        xd=xDest-xPos;
        yd=yDest-yPos;

        // Euclidian Distance
        d=static_cast<int>(sqrt(xd*xd+yd*yd));

        // Manhattan distance
        //d=abs(xd)+abs(yd);

        // Chebyshev distance
        //d=max(abs(xd), abs(yd));

        return(d);
    }
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
    return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
string pathFind( const int & xStart, const int & yStart,
                 const int & xFinish, const int & yFinish )
{
    static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static node* n0;
    static node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

    // reset the node maps
    for(y=0; y<m; y++)
    {
        for(x=0; x<n; x++)
        {
            closed_nodes_map[x][y]=0;
            open_nodes_map[x][y]=0;
        }
    }

    // create the start node and push into list of open nodes
    n0=new node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[x][y]=n0->getPriority(); // mark it on the open nodes map

    // A* search
    while(!pq[pqi].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
        n0=new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
                     pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x=n0->getxPos();
        y=n0->getyPos();

        pq[pqi].pop(); // remove the node from the open list
        open_nodes_map[x][y]=0;
        // mark it on the closed nodes map
        closed_nodes_map[x][y]=1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if(x==xFinish && y==yFinish)
        {
            // generate the path from finish to start
            // by following the directions
            string path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                c='0'+(j+dir/2)%dir;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            // garbage collection
            delete n0;
            // empty the leftover nodes
            while(!pq[pqi].empty())
                pq[pqi].pop();
            return path;
        }

        // generate moves (child nodes) in all possible directions
        for(i=0; i<dir; i++)
        {
            xdx=x+dx[i];
            ydy=y+dy[i];

            if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || map[xdx][ydy]==1
                    || closed_nodes_map[xdx][ydy]==1))
            {
                // generate a child node
                m0=new node( xdx, ydy, n0->getLevel(),
                             n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                // if it is not in the open list then add into that
                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    pq[pqi].push(*m0);
                    // mark its parent node direction
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                }
                else if(open_nodes_map[xdx][ydy]>m0->getPriority())
                {
                    // update the priority info
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(pq[pqi].top().getxPos()==xdx &&
                            pq[pqi].top().getyPos()==ydy))
                    {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pq[pqi].pop(); // remove the wanted node

                    // empty the larger size pq to the smaller one
                    if(pq[pqi].size()>pq[1-pqi].size())
                        pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0); // add the better node instead
                }
                else
                    delete m0; // garbage collection
            }
        }
        delete n0; // garbage collection
    }
    return ""; // no route found
}

void print(int  m, int  n,int  map[][map_x_Size])




{
    for(int y=0; y<m; y++)
    {
        for(int x=0; x<n; x++)
        {
            CursorPosition(x,y);
            ShowConsoleCursor(false);
            if(map[x][y]==0)
                cout<<".";
            else if(map[x][y]==1)
            {
                SetConsoleTextAttribute(color,12);
                cout<<"X"; //obstacle
                SetConsoleTextAttribute(color,7);

            }

            else if(map[x][y]==2)

                cout<<"S"; //start

            else if(map[x][y]==3)
            {
                SetConsoleTextAttribute(color,11);
                cout<<"S"; //route
                SetConsoleTextAttribute(color,7);
            }

            else if(map[x][y]==4)
                cout<<"F"; //finish
            else if(map[x][y]==5)
            {
                SetConsoleTextAttribute(color,24);
                cout<<"P";

                SetConsoleTextAttribute(color,7);
            }
            else if(map[x][y]==6)

                cout<<"S";
            else if(map[x][y]==8)
            {
                SetConsoleTextAttribute(color,10);
                cout<<"o";
                SetConsoleTextAttribute(color,7);
            }
        }
        cout<<endl;
    }
    Sleep(20);// wait for enter key
}

string compare(int a[],string b[], int c, int end_point_flag[],int boxnumber,int& box_end_point_index)
//this function can choose the shortest point for each starting point and
// it would not have a redundant finish point for 2 starting point.
{
    int i=c-boxnumber;                     //i is start index;
    int location=0;              // end_point_flag determined wheather end_point is used


    for(int j=i+1; j<c; j++)
    {
        if(a[i]>a[j])
            location=j;             //compare the length of each route

        else
            location=i;
        i=j;

    }

    if(end_point_flag[location]==0)  //if the end_point never been used
    {
        end_point_flag[location]=1;
        end_point_flag[location+boxnumber]=1;
        end_point_flag[location+(boxnumber*2)]=1;
        box_end_point_index=location%boxnumber;
        return b[location];
    }

    else if (end_point_flag[location]==1&&end_point_flag[location+1]==0&&location%boxnumber==0) //if the end point is used and next end point is not used
    {
        end_point_flag[location+1]=1;
        end_point_flag[location+(boxnumber+1)]=1;
        end_point_flag[location+((boxnumber*2)+1)]=1;
        box_end_point_index=(location%boxnumber)+1;
        return b[location+1];
    }
    else if (end_point_flag[location]==1&&end_point_flag[location+1]==1&&location%boxnumber==0) //if the current end point and next end
    {
                                                                                                //point also been used (for 3 boxes case)
        end_point_flag[location+2]=1;                                                           //the shortest path to the 1st end point
        end_point_flag[location+5]=1;
        end_point_flag[location+8]=1;
        box_end_point_index=(location%boxnumber)+2;
        return b[location+2];
    }
    else if (end_point_flag[location]==1&&end_point_flag[location-1]==0&&location%boxnumber==1)
    {
        end_point_flag[location-1]=1;
        end_point_flag[location+(boxnumber-1)]=1;
        end_point_flag[location+((boxnumber*2)-1)]=1;
        box_end_point_index=(location%boxnumber)-1;
        return b[location-1];
    }
    else if (end_point_flag[location]==1&&end_point_flag[location-1]==1&&location%boxnumber==1)
    {
        end_point_flag[location+1]=1;
        end_point_flag[location+4]=1;
        end_point_flag[location+7]=1;
        box_end_point_index=(location%boxnumber)+1;
        return b[location+1];
    }
    else if (end_point_flag[location]==1&&end_point_flag[location-1]==1&&location%boxnumber==2)
    {
        end_point_flag[location-2]=1;
        end_point_flag[location+1]=1;
        end_point_flag[location+4]=1;
        box_end_point_index=(location%boxnumber)-2;
        return b[location-2];
    }
    else if (end_point_flag[location]==1&&end_point_flag[location-1]==0&&location%boxnumber==2)
    {
        end_point_flag[location-1]=1;
        end_point_flag[location+2]=1;
        end_point_flag[location+5]=1;
        box_end_point_index=(location%boxnumber)-1;

        return b[location-1];
    }



    return 0;
}
int main()
{

    //this part initialize the map



    mapcalling(n,m,map);

    // this part define  start and finish locations //the start is box and the end is the finish point.
    int start_x[]= box_init_position_x, start_y[]= box_init_position_y; // box location
    int  end_x[]= final_point_x, end_y[]= final_point_y; // ending point location
    int person_x=person_init_position_x, person_y=person_init_position_y; // person location



    print(n,m,map);




// local definition
    int path_cost_length[10];
    string box_route;
    string box_route_data[10];
    string human_route;
    // the selected human_route after compare. // to prevent collision of box in same finish point
    string human_route_data[10];
    int end_point_flag[10]= {0}; // flag to determine whether an end-point is used or not
    int new_start_x;   // the new point to start (from person to 2nd box)after the fist job is done
    int new_start_y;





// the core part start here
    for( int i=0; i<boxnumber; i++)  //for every push box job

    {

        CursorPosition(0,map_y_Size+1);cout<<"                                   "<<endl;
        CursorPosition(0,map_y_Size+2);cout<<"                                   "<<endl;
        CursorPosition(0,map_y_Size+3);cout<<"                                   "<<endl;
        CursorPosition(0,map_y_Size+4);cout<<"                                   "<<endl;
        CursorPosition(0,map_y_Size+5);cout<<"                                   "<<endl;
        CursorPosition(0,map_y_Size+6);cout<<"                                   "<<endl;
        CursorPosition(0,map_y_Size+7);cout<<"                                   "<<endl;
        CursorPosition(0,map_y_Size+8);cout<<"                                   "<<endl;
        CursorPosition(0,map_y_Size+9);cout<<"                                   "<<endl;
         CursorPosition(0,map_y_Size+10);cout<<"                                   "<<endl;

        CursorPosition(0,map_y_Size);

        cout<<"Map Size (X,Y): "<<n<<","<<m<<endl;
        cout<<"coordinate of "<<i+1<< "set"<<endl<<"this is the human properties"<<endl;
        cout<<"Start: "<<person_x<<","<<person_y<<endl;
        cout<<"Finish: "<<start_x[i]<<","<<start_y[i]<<endl;

        human_route=pathFind(person_x,person_y,start_x[i],start_y[i]);
        // cout<<"The human route is"<<human_route<<endl;




        int box_end_point_index=0;
        int j;
        int box=boxnumber;// some local variable to manipulate the display of the game
        char c;
        int x=person_x;
        int y=person_y;

        while((box-1)>=i) // while i>=box
        {

            map[end_x[box-1]][end_y[box-1]]=4;

            map[start_x[box-1]][start_y[box-1]]=2;

            box--;
        }


        if(i==0)
        {
            map[x][y]=5;
        }
        else
        {

            map[x][y]=7;
        }

        if(i==2)

        {
            map[end_x[2]][end_y[2]]=4;
        }







        for(int i=0; i<human_route.length(); i++)
        {

            for(int y=0; y<m; y++)
            {
                for(int x=0; x<n; x++)
                {
                    CursorPosition(x,y);
                    ShowConsoleCursor(false);
                    if(map[x][y]==0)
                        cout<<".";
                    else if(map[x][y]==1)
                    {
                        SetConsoleTextAttribute(color,12);

                        cout<<"X"; //obstacle
                        SetConsoleTextAttribute(color,7);
                    }

                    else if(map[x][y]==2)
                    {
                        SetConsoleTextAttribute(color,11);
                        cout<<"S"; //start
                        SetConsoleTextAttribute(color,7);

                    }


                    else if(map[x][y]==4)
                    {
                        SetConsoleTextAttribute(color,14);
                        cout<<"F"; //finish
                        SetConsoleTextAttribute(color,7);
                    }
                    else if(map[x][y]==5)
                    {
                        SetConsoleTextAttribute(color,24);
                        cout<<"P";
                        map[x][y]=0;
                        SetConsoleTextAttribute(color,7);
                    }
                    else if(map[x][y]==6)
                    {
                        SetConsoleTextAttribute(color,24);
                        cout<<"P";
                        map[x][y]=0;
                        SetConsoleTextAttribute(color,7);
                    }
                    else if(map[x][y]==7)
                    {
                        SetConsoleTextAttribute(color,11);
                        cout<<"S"; //start
                        SetConsoleTextAttribute(color,7);

                    }
                    else if(map[x][y]==8)
                    {
                        SetConsoleTextAttribute(color,10);
                        cout<<"o";
                        SetConsoleTextAttribute(color,7);
                    }

                }

                cout<<endl;
            }
            Sleep(20);
            c =human_route.at(i); //for each and every state of the human route
            j=atoi(&c);



            x=x+dx[j];
            y=y+dy[j];

            if (map[x][y]==8) //if encounter bush, need additional one enter key to move
            {
                Sleep(20);
            }


            map[x][y]=6;


        }



        for (int j=0; j<boxnumber; j++) //find every possible path to finish point for each box
        {

            box_route=pathFind(start_x[i], start_y[i], end_x[j], end_y[j]); //fing the path from box to finish point

            box_route_data[(i*boxnumber)+j]=box_route; //record the path data

            path_cost_length[(i*boxnumber)+j]= box_route.length(); //record the path length

            //cout<<box_route<<endl;


        }

        // calling compare function to find the best route for each box // return the index of selected end-point
        string route_2=compare(path_cost_length,box_route_data,(i*boxnumber)+boxnumber,end_point_flag,boxnumber,box_end_point_index);
        cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"this is the box properties"<<endl;
        cout<<"Start: "<<start_x[i]<<","<<start_y[i]<<endl;
        cout<<"Finish: "<<end_x[box_end_point_index]<<","<<end_y[box_end_point_index]<<endl;




        int box2=boxnumber-1; //some local variable to manipulate the display

        while((box2)>=i) // while i>=box
        {
            map[start_x[box2]][start_y[box2]]=6;

            box2--;
        }



        if(route_2.length()>0)
        {
            int j;
            char c;
            int x=start_x[i];
            int y=start_y[i];




            map[x][y]=2;

            if(i==2)
            {
                map[end_x[2]][end_y[2]]=4;
            }



            for(int i=0; i<route_2.length(); i++)
            {
                for(int y=0; y<m; y++)
                {
                    for(int x=0; x<n; x++)
                    {
                        CursorPosition(x,y);
                         ShowConsoleCursor(false);

                        if(map[x][y]==0)
                            cout<<".";
                        else if(map[x][y]==1)
                        {
                            SetConsoleTextAttribute(color,12);

                            cout<<"X"; //obstacle
                            SetConsoleTextAttribute(color,7);
                        }
                        else if(map[x][y]==2)
                        {
                            SetConsoleTextAttribute(color,11);
                            cout<<"S";//start
                            map[x][y]=0;
                            SetConsoleTextAttribute(color,7);
                        }

                        else if(map[x][y]==3)
                        {
                            SetConsoleTextAttribute(color,11);
                            cout<<"S";//route
                            map[x][y]=0;
                            SetConsoleTextAttribute(color,7);
                        }

                        else if(map[x][y]==4)
                        {
                            SetConsoleTextAttribute(color,14);
                            cout<<"F"; //finish
                            SetConsoleTextAttribute(color,7);
                        }

                        else if(map[x][y]==5)
                        {
                            SetConsoleTextAttribute(color,24);
                            cout<<"P";
                            map[x][y]=0;
                            SetConsoleTextAttribute(color,7);
                        }
                        else if(map[x][y]==6)
                        {
                            SetConsoleTextAttribute(color,11);
                            cout<<"S";
                            SetConsoleTextAttribute(color,7);

                        }
                        else if(map[x][y]==8)
                        {
                            SetConsoleTextAttribute(color,10);
                            cout<<"o";
                            SetConsoleTextAttribute(color,7);
                        }

                    }
                    cout<<endl;
                }
                Sleep(20);
                c =route_2.at(i);
                j=atoi(&c);

                map[x][y]=5; // printf P one step before the box
                x=x+dx[j];
                y=y+dy[j];

                if (map[x][y]==8)
                {
                    Sleep(20);
                }
                new_start_x=x;
                new_start_y=y;

                map[x][y]=3;

            }
        }

        person_x=new_start_x;  //renew the start point
        person_y=new_start_y;

        print(n,m,map);

    }


    return(0);
}
