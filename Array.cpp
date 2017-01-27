#include "Array.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

Array::Array()
{

}
void Array::insertArray(const int toInsert[],int w,int h,Vector2u origine1,Vector2u origine2)
{
    int nb=0;
    int k=0;

        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                if((j>=(int)origine1.x) && (i>=(int)origine1.y) && (j<=(int)origine2.x) && (i<=(int)origine2.y))
                {
                  //cout<<i<<"||"<<j<<endl;
                  tableau[nb]=toInsert[k];
                  tab_collision[i][j]=FILL;
                  k++;
                }
                nb++;
            }
        }

    nb=0;

}

int Array::getTab(int i)
{
return tableau[i] ;
}
void Array::insertElement(int toInsert,int w,int h,Vector2u origine1,Vector2u origine2)
{

    int nb=0;
    int k=0;

        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                if((j>=(int)origine1.x) && (i>=(int)origine1.y) && (j<=(int)origine2.x) && (i<=(int)origine2.y))
                {
                 tableau[nb]=toInsert;
                 k++;
                }
                nb++;
            }
        }
        //setCollision();//origine1,origine2,w,h);
}
void Array::initArray(int w,int h)
{
    int nb=0;

     for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
            tableau[nb]=22;
            nb++;
            }}
}
void Array::initCollision()
{
    int i,j;


    for(i=0;i<SizeArrayH;i++)
    {
         for(j=0;j<SizeArrayW;j++)
         {
            tab_collision[i][j]=EMPTY;
         }
    }
}

int Array::getCollision(int x,int y,string direction)
{


    int collision=0;
    if(direction=="Right")
    {
       if(tab_collision[(y/16)][(x/16)+1]==1)
        {
        collision=1;
        }
        else
        {
        collision=0;
        }
    }
    if(direction=="Left")
    {
       if(tab_collision[(y/16)][(x/16)-1]==1)
        {
        collision=1;
        }
        else
        {
        collision=0;
        }
    }
    if(direction=="Up")
    {
       if(tab_collision[(y/16)-1][(x/16)]==1)
        {
        collision=1;
        }
        else
        {
        collision=0;
        }
    }
    if(direction=="Down")
    {
       if(tab_collision[(y/16)+1][(x/16)]==1)
        {
        collision=1;
        }
        else
        {
        collision=0;
        }
    }


return collision;
}
void Array::setCollision()//Vector2u origine1,Vector2u origine2,int w,int h)
{
    int i,j;
    for(i=0;i<SizeArrayH;i++)
    {
        for(j=0;j<SizeArrayW;j++)
        {
            cout<<tab_collision[i][j];
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}




