#include "map3.h"

#include<iostream>
using namespace std;
void mapcalling(int  m , int  n, int map[][map_x_Size])
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


// this part defining the bush part
    for(int x=16; x<24; x++)

    {
        for(int y=14; y<17; y++)
        {
            map[x][y]=8;
        }

    }

 for(int x=15; x<18; x++)

    {
        for(int y=17; y<20; y++)
        {
            map[x][y]=8;
        }

    }
 for(int i=17; i<19; i++)
 {
     map[18][i]=1;
 }

  for(int i=20; i<23; i++)
 {
     map[18][i]=1;
 }

  for(int i=19; i<24; i++)
 {
     map[i][17]=1;
 }

 for(int i=19; i<23; i++)
 {
     map[20][i]=1;
 }

  for(int i=21; i<24; i++)
 {
     map[i][19]=1;
 }
 for (int l=6; l<=10; l++)
     {
    map[l][2]=1;
    map[l][4]=1;
     }


map[17][20]=8;
map[17][21]=8;
map[15][21]=8;
map[15][22]=8;
map[15][23]=8;
map[16][23]=8;
map[17][23]=8;

for (int l=6; l<13; l++)
    {

    map[l][4]=1;

    }
     for (int l=7 ;l<11; l++)
    {
        map [l][7] = 1;
    }
    map[8][1]=1;
    map [8][8] =1;
    map [9][8] =1;
    map [9][9] =1;
    map [10][9] =1;
    map [7][9] =1;
    map [7][13] =1;
    map [7][11] =1;
    map [8][9] =1;
    map [2][5] =1;
    map [3][6] =1;
    map [4][7] =1;
    map [2][7] =1;
    map [4][5] =1;
    map [5][4]=1;
    map [1][1] =1;
    map [1][2] =1;
    map [2][1]=1;
     for (int i=9; i<12; i++)
    {
        map [12][i] = 1;
    }

    map [11][10] =1;
    map [13][10]=1;

    for (int l=1 ;l<6; l++)
    {
        map [l][9] = 1;
    }

    for (int i=10; i<13; i++)
    {
        map [5][i] = 1;
    }

     for (int l=2 ;l<5; l++)
    {
        map [l][12] = 1;
    }

    for(int l=9; l<11; l++)
    {
        for(int i=11; i<13; i++)
        {
            map [l][i] =1;
        }
    }

        for(int i=1; i<13; i++)
        {
            map [i][15] =1;
        }

        for(int i=2; i<13; i++)
        {
            map [i][22] =1;
        }

           for(int i=17; i<22; i++)
        {
            map [2][i] =1;
        }

        for(int i=16; i<23; i++)
        {
            map [13][i] =1;
        }

        for(int l=3; l<12; l++)
    {


            map [l][17] =1;

    }

     for(int l=18; l<21; l++)
    {


            map [11][l] =1;

    }
    for(int l=4; l<11; l++)
    {


            map [l][20] =1;

    }


map [22][2] =8;
map [21][3] =1;
map [20][4] =1;
map [19][5] =1;
map [18][6] =1;
map [17][7] =1;
map [16][8] =1;
map [15][9] =1;
map [15][10] =8;
map [14][11] =8;
map [13][12] =8;
map [13][13] =8;
map [12][14] =8;

map [13][1] =1;
map [14][2] =1;
map [15][3] =1;
map [16][4] =1;
map [17][5] =1;
map [18][6] =1;
map [19][7] =1;
map [20][8] =1;
map [21][9] =8;
map [22][10] =8;
map [23][11] =8;

for(int l=1; l<13; l++)
    {

            map [18][l] =1;

    }


            map [19][6] =1;
            map [20][6] =1;
            map [21][6] =8;
            map [22][6] =1;
            map [23][6] =1;



}


