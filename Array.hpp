#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>

const int SizeArrayH=22;
const int SizeArrayW=45;
const int EMPTY=0;
const int FILL =1;


using namespace sf;
using namespace std;


class Array
{
    private:
        //int tableau[1000];

    public:
        int collision[SizeArrayH*SizeArrayW];
        list<int> tabBloc;
        int ncollision;
        int tableau[SizeArrayH*SizeArrayW];
        int tab_collision[SizeArrayH][SizeArrayW];
        Array();
        void insertArray(const int toInsert[],int w,int h,Vector2u origine1,Vector2u origine2);
        void insertElement(int toInsert,int w,int h,Vector2u origine1,Vector2u origine2);
        void initArray(int,int);
        void initCollision();
        int getCollision(int x,int y,string direction);//int*);
        void setCollision();//Vector2u origine1,Vector2u origine2,int w,int h);
        int getTab(int);


};
#endif
