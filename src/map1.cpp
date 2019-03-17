#include "map1.h"

#include<iostream>
using namespace std;
void mapcalling(int  m , int  n, int   map[][map_x_Size])
{
 // create empty map
    for(int y=0; y<m; y++)
    {
        for(int x=0; x<n; x++)
            map[x][y]=0;
    }

    // this part defining the obstacles of the map.
    for(int x=0; x<n; x++)

    {
        for(int y=0; y<m; y++)
        {
            if (x==0||x==n-1||y==0 ||y==m-1 || (x<n-10&&y<n-10)|| (x>10&&y>10)||(x>7&&x<11&&y>7&&y<12))
                map[x][y]=1;
        }

    }

    map[2][11]=1;
    map[3][11]=1;
    map[4][11]=1;
    map[5][11]=1;
    map[6][11]=1;
    map[7][11]=1;
// this part defining the bush part
    for(int x=8; x<11; x++)

    {
        for(int y=1; y<8; y++)
        {
            map[x][y]=8;
        }

    }



}


