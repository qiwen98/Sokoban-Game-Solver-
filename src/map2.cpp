#include "map2.h"
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
            if (x==0||x==n-1||y==0 ||y==m-1 )
                map[x][y]=1;
        }

    }


    // this part defining the obstacles of the map.




    map[6][1]=1;
    map[7][1]=1;
    map[8][1]=1;
    map[9][1]=1;
    map[10][1]=1;
    for (int l=1; l<=6; l++)
    {
    map[l][11]=1;
    }
    for (int l=5; l<=10; l++)
     {
    map[l][2]=1;
    map[l][4]=1;
     }

    for (int l=6; l<n; l++)
    {

    map[l][4]=1;

    }
    map [7][7] =1;
    map [8][7] =1;
    map [8][8] =1;
    map [9][8] =1;
    map [9][9] =1;
    map [10][9] =1;
    map [7][13] =1;
    map [7][11] =1;

    for(int l=9; l<11; l++)
    {
        for(int i=11; i<13; i++)
        {
            map [l][i] =1;
        }
    }

     for (int l=12; l<18; l++)
    {
    map[l][12]=1;
    }

    map[12][13]=1;
    map[12][14]=1;
    map[12][15]=1;
    map[12][16]=1;
    map[12][17]=1;
  for (int l=13; l<17; l++)
    {
    map[l][17]=1;
    }

map[16][16]=1;
for (int l=15; l<18; l++)
{
map[l][15]=1;
}

map[2][16]=1;
map[3][16]=1;
map[3][17]=1;
map[2][13]=1;
map[2][14]=1;
map[3][14]=1;

map[5][14]=1;
map[6][13]=1;
map[6][14]=1;
map[5][17]=1;
map[5][16]=1;
map[6][16]=1;
for (int l=1; l<6; l++)
{
map[l][6]=1;
}
for (int l=7; l<10; l++)
{
map[5][l]=1;
}

for (int l=1; l<19; l++)
{
map[l][18]=8;
}

for(int l=9; l<11; l++)
    {
        for(int i=13; i<18; i++)
        {
            map [l][i] =8;
        }
    }

    for (int l=12; l<18; l++)
{
map[l][6]=8;
}

 for (int l=7; l<11; l++)
{
map[12][l]=8;
}

for (int l=13; l<17; l++)
{
map[l][10]=8;
}

map[17][8]=8;
map[16][8]=8;
map[15][8]=8;
map[16][9]=8;

}
