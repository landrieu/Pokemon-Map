#include "Jeu.hpp"
#include "TileMap.hpp"
#include "Array.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <windows.h>

using namespace sf;
using namespace std;

string DOWN="Down";
string UP="Up";
string RIGHT="Right";
string LEFT="Left";
string JEU="Jeu";
string PAUSE="Pause";
int SizeWindowH=352;
int SizeWindowW=720;

// Decalre each element of the map, the numbers match with the position in the file map.png
const int TLake[]=
{
    115,116,116,
    138,140,140,
    138,140,140,
    138,140,140,
    138,140,140,
    138,140,140,
    207,208,208,
};
const int TSapin[]=
{
    17,40,63,
};
const int THouse[25]=
{
    9,10,11,12,13,
    32,33,34,35,36,
    55,56,57,58,59,
    78,79,80,81,82,
    101,102,103,104,105,
};
const int TBigTree[]=
{
    230,231,232,
    253,254,255,
    276,277,278,
    299,300,301,

};
/*
const int TShop2[2][16]=
{
    {5,6,7,8,28,29,30,31,51,52,53,54,74,75,76,77},
    {0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0},

};*/
const int TShop[]=
{
    5,6,7,8,
    28,29,30,31,
    51,52,53,54,
    74,75,76,77,

};
const int TPoke[]=
    {
        0, 1, 2, 3, 4,
        23,24,25,26,27,
        46,47,48,49,50,
        69,70,71,72,73,
        92,93,94,95,96,

    };
const int level[] =
    {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 15, 15, 15, 15,
        23, 24, 25, 26, 27, 28, 29, 30, 31, 74, 75, 2, 15, 15, 15, 15,
        46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 3, 3, 3, 3, 3, 3,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 3, 3, 3, 3, 3, 3,
        92,93,94,95,96,15,15,15,100,101,102,103,104,105,106,107,
    };


Jeu::Jeu(){

}

int Jeu::jouer(){
/****************************Déclarations***********************************/
    int mouseX,mouseY;
    int flag_move=0,Collision=0;
    Event event;
    Font Police,Sixty;
    Texture texture_front,thouse,tdresseur2;
    Texture tdresseur_face,tdresseur_back,tdresseur_side;
    Texture tdresseur_face_move,tdresseur_back_move,tdresseur_side_move;
    Text text,textPause;
    Clock clk;
    Time elapsed1,elapsed2;
    Sprite dresseur1,dresseur2,house;
    Sprite dresseur_face,dresseur_back,dresseur_sideL,dresseur_sideR;
    Sprite dresseur_face_move,dresseur_back_move,dresseur_sideL_move,dresseur_sideR_move;
    Image dresseur;
    //IntRect area_face(41,44,16,16),area_back(57,43,16,16),area_side(75,43,16,16);//sasha gold
    IntRect area_face(6,9,16,19),area_back(113,9,16,19),area_side(59,9,16,19);
    IntRect area_face_move(24,9,16,19),area_back_move(132,9,16,19),area_side_move(77,9,16,19);
    char* temps="TIME";
    temps = (char*)malloc(sizeof(char));
    string MOVE=DOWN;
    string MODE=JEU;
    string str;
    Array tab1;
    stringstream out;
    Image icone;
    int i;

    TileMap map,house_m,shop_m,poke_m,test_m;
    //Former piece of code of the game
    if (!map.load("Image/Map.png", sf::Vector2u(16, 16), level, 16, 5))
        return -1;
    if (!poke_m.loadt("Image/Map.png", sf::Vector2u(16, 16), TPoke, 5, 5,28,10))
        return -1;
    if (!shop_m.loadt("Image/Map.png", sf::Vector2u(16, 16), TShop, 4, 4,2,10))
        return -1;
     if (!house_m.loadt("Image/Map.png", sf::Vector2u(16, 16), THouse, 5, 5,0,8))
        return -1;

     tab1.initCollision();//Create an array fill with 0, it will be useful to manage the collisions later



     tab1.initArray(SizeArrayW,SizeArrayH);
     tab1.insertElement(15,45,22,Vector2u(0,0),Vector2u(44,21));//15 correspond to the grass, it's at the 15th position in the file map.png
     tab1.insertElement(84,45,22,Vector2u(1,1),Vector2u(5,2));//84 correspond to the flowers //45 and 22 correspond to the size of the map -> 352/16 = 22 and 720/16=45
     tab1.insertElement(61,45,22,Vector2u(0,18),Vector2u(10,21));//the two last argument correspond to the place where the first element will be placed
     tab1.insertElement(83,45,22,Vector2u(26,SizeArrayH-5),Vector2u(26,SizeArrayH));//the two argument correspond to the place where the last element will be placed

     tab1.insertArray(TShop,SizeArrayW,SizeArrayH,Vector2u(15,10),Vector2u(18,13));// in this case the house has been defined previously
     //tab1.insertArray(THouse,SizeArrayW,SizeArrayH,Vector2u(5,3),Vector2u(9,7));// This function place the building on the map
    tab1.insertArray(TPoke,SizeArrayW,SizeArrayH,Vector2u(32,5),Vector2u(36,9));
    tab1.insertArray(THouse,SizeArrayW,SizeArrayH,Vector2u(5,3),Vector2u(9,7));
    tab1.insertArray(THouse,SizeArrayW,SizeArrayH,Vector2u(15,3),Vector2u(19,7));
    for(i=0;i<11;i++)
        tab1.insertArray(TSapin,SizeArrayW,SizeArrayH,Vector2u(i,15),Vector2u(i,17));

    tab1.insertArray(TLake,SizeArrayW,SizeArrayH,Vector2u(SizeArrayW-3,5),Vector2u(SizeArrayW,11));
    tab1.insertArray(TBigTree,SizeArrayW,SizeArrayH,Vector2u(32,17),Vector2u(34,20));
    tab1.setCollision();
    // At this point the array tab1 is fill with number
     if (!test_m.load("Image/Map.png", sf::Vector2u(16, 16), tab1.tableau, SizeArrayW, SizeArrayH))
        return -1;
    // Get the sprite from the file Map.png


/********************************Chargement Police et Sprites****************************************/
    if (!Police.loadFromFile("Image/calibri.ttf")||!Sixty.loadFromFile("Image/Sixty.ttf"))
    {
                  cout <<"Erreur lors du chargement de la police"<<endl;
                     return -1;
    }
    if (!icone.loadFromFile("Image/pokeball.png"))
        return -1;
    setIcon(32,32,icone.getPixelsPtr());                 //modifier l'icone de la fenetre

    text.setFont(Police);
	text.setCharacterSize(24);
    text.setString("TIME:");
    text.setPosition(SizeWindowW-100,0);
    text.setColor(Color::Black);
    textPause.setFont(Sixty);
    textPause.setPosition((SizeWindowW/2)-50,(SizeWindowH/2)-40);
    textPause.setString("Pause");
    textPause.setColor(Color::Black);

    if (!dresseur.loadFromFile("Image/Sacha.png"))// Load the file Sacha.png
    {
      return -1;
    }
    else
    {
        //dresseur.createMaskFromColor(Color::Green,10);//transparency to the green color
        dresseur.createMaskFromColor(Color::White,10);//
        tdresseur_face.loadFromImage(dresseur,area_face);// Create 3 textures
        tdresseur_back.loadFromImage(dresseur,area_back);
        tdresseur_side.loadFromImage(dresseur,area_side);

        tdresseur_face_move.loadFromImage(dresseur,area_face_move);// Texture for the move
        tdresseur_back_move.loadFromImage(dresseur,area_back_move);
        tdresseur_side_move.loadFromImage(dresseur,area_side_move);

        //tdresseur2.setFillColor(White);
        dresseur_face.setTexture(tdresseur_face);
        dresseur_back.setTexture(tdresseur_back);
        dresseur_sideL.setTexture(tdresseur_side);

        dresseur_face_move.setTexture(tdresseur_face_move);
        dresseur_back_move.setTexture(tdresseur_back_move);
        dresseur_sideL_move.setTexture(tdresseur_side_move);

        dresseur_sideR=dresseur_sideL;
        dresseur_sideR.setTextureRect(sf::IntRect(16, 0, -16, 19));//Reverse the side texture to get the left image of Sacha
        dresseur_sideR_move=dresseur_sideL_move;
        dresseur_sideR_move.setTextureRect(sf::IntRect(16, 0, -16, 19));

        dresseur1=dresseur_sideR;//Place the player on the map
        dresseur1.setPosition(0,0);
    }

    /*if (!texture_front.loadFromFile("Image/Sacha_gold.png"))
    {
        return -1;
    }
    else
    {
        texture_front.setSmooth(true);
        dresseur1.setTexture(texture_front);
        dresseur1.setPosition(0,0);
    }*/
    if (!thouse.loadFromFile("Image/House.png"))
    {
        return -1;
    }
    else
    {
        thouse.setSmooth(true);
        house.setTexture(thouse);
        house.setPosition(100,100);
    }


/****************************Ouverture de la fenetre*************************************************************/
    create(VideoMode(SizeWindowW,SizeWindowH),"POKEMON");//Create the window

    setFramerateLimit(30);
/******************************Gestion des évènements************************************************************/
     while(this->isOpen())
     {
            if(flag_move==1)
            {
                if(MOVE==RIGHT)
                {
                  dresseur_sideR.setPosition(dresseur1.getPosition().x+8,dresseur1.getPosition().y);
                  dresseur1=dresseur_sideR;
                }
                if(MOVE==LEFT)
                {
                  dresseur_sideL.setPosition(dresseur1.getPosition().x-8,dresseur1.getPosition().y);
                  dresseur1=dresseur_sideL;
                }
                if(MOVE==UP)
                {
                  dresseur_back.setPosition(dresseur1.getPosition().x,dresseur1.getPosition().y-8);
                  dresseur1=dresseur_back;
                }
                if(MOVE==DOWN)
                {
                  dresseur_face.setPosition(dresseur1.getPosition().x,dresseur1.getPosition().y+8);
                  dresseur1=dresseur_face;
                }

              flag_move=0;
            }



             itoa(clk.getElapsedTime().asSeconds(),temps,10);
             str.append(temps);
             text.setString("TIME: " + str);
             str.clear();

            while (pollEvent(event))
                {                             //boucle des événements

                switch (event.type)
                {

                    case Event::Closed:                                 //si on ferme la fenetre
                    close();
                    break;

                    case Event::KeyPressed:
                       //elapsed1=clk.getElapsedTime();



                                                    //si on appuie sur une touche
                    if (event.key.code==Keyboard::Escape)
                        close();
                    if (event.key.code==Keyboard::Space)
                    {
                        if(MODE==PAUSE)
                        {
                         MODE=JEU;
                        }
                        else
                        {
                         elapsed1=clk.getElapsedTime();
                         MODE=PAUSE;
                        }
                    }


                    /*******************************Déplacements******************************************/

                    if(MODE!=PAUSE && (clk.getElapsedTime().asSeconds()-elapsed2.asSeconds()>.1) )
                    {
                        elapsed2=clk.getElapsedTime();

                    if (event.key.code==Keyboard::Right )//&& dresseur1.getPosition().x<getSize().x-20)
                    {
                      dresseur_sideR.setPosition(dresseur1.getPosition().x,dresseur1.getPosition().y);
                      dresseur1=dresseur_sideR;
                      Collision=tab1.getCollision(dresseur1.getPosition().x,dresseur1.getPosition().y,RIGHT);
                      if(MOVE==RIGHT && dresseur1.getPosition().x<getSize().x-20 && Collision==0)
                      {
                      flag_move=1;
                      dresseur_sideR_move.setPosition(dresseur1.getPosition().x+8,dresseur1.getPosition().y);
                      dresseur1=dresseur_sideR_move;
                      }
                      MOVE=RIGHT;
                    }

                    if (event.key.code==Keyboard::Left )// && dresseur1.getPosition().x>0)
                    {
                      dresseur_sideL.setPosition(dresseur1.getPosition().x,dresseur1.getPosition().y);
                      dresseur1=dresseur_sideL;
                      Collision=tab1.getCollision(dresseur1.getPosition().x,dresseur1.getPosition().y,LEFT);
                      if(MOVE==LEFT && dresseur1.getPosition().x>0 && Collision==0)
                      {
                      flag_move=1;
                      dresseur_sideL_move.setPosition(dresseur1.getPosition().x-8,dresseur1.getPosition().y);
                      dresseur1=dresseur_sideL_move;
                      }
                      MOVE=LEFT;
                    }

                    if (event.key.code==Keyboard::Up )// && dresseur1.getPosition().y>0)
                    {
                      dresseur_back.setPosition(dresseur1.getPosition().x,dresseur1.getPosition().y);
                      dresseur1=dresseur_back;
                      Collision=tab1.getCollision(dresseur1.getPosition().x,dresseur1.getPosition().y,UP);
                      if(MOVE==UP && dresseur1.getPosition().y>0 && Collision==0)
                      {
                       flag_move=1;
                       dresseur_back_move.setPosition(dresseur1.getPosition().x,dresseur1.getPosition().y-8);
                       dresseur1=dresseur_back_move;
                      }
                      MOVE=UP;
                    }

                    if (event.key.code==Keyboard::Down )//&& dresseur1.getPosition().y<getSize().y-20)
                    {
                       dresseur_face.setPosition(dresseur1.getPosition().x,dresseur1.getPosition().y);
                       dresseur1=dresseur_face;
                       Collision=tab1.getCollision(dresseur1.getPosition().x,dresseur1.getPosition().y,DOWN);
                       if(MOVE==DOWN && dresseur1.getPosition().y<getSize().y-20 && Collision==0)
                       {
                        flag_move=1;
                        dresseur_face_move.setPosition(dresseur1.getPosition().x,dresseur1.getPosition().y+8);
                        dresseur1=dresseur_face_move;
                       }
                       MOVE=DOWN;
                    }
                    }

                    break;

                    case Event::MouseButtonPressed:
                        if (event.mouseButton.button==Mouse::Left)
                            {             //bouton gauche
                            mouseX=Mouse::getPosition(*this).x;            //on recupere la position de la souris
                            mouseY=Mouse::getPosition(*this).y;
                            }
                    break;
                    default:
                    break;
                }


            }


 /***********************************Affichage**************************************************/
    clear(Color(255,255,255));
   //clear(Color(97,176,86));
     draw(test_m);

    draw(dresseur1);

    draw(text);


    if(MODE==PAUSE)
    {

        if(((clk.getElapsedTime().asSeconds()-elapsed1.asSeconds())>0.5)&&textPause.getColor()==Color::Black)
        {
        textPause.setColor(Color::Red);
        elapsed1=clk.getElapsedTime();
        //text.setString(std::to_String(elapsed1));
        }
        if(((clk.getElapsedTime().asSeconds()-elapsed1.asSeconds())>0.5)&&textPause.getColor()==Color::Red)
        {
        textPause.setColor(Color::Black);
        elapsed1=clk.getElapsedTime();
        }
            draw(textPause);


    }


    //draw(poke_m);
    //draw(shop_m);

    //draw(map);

    //draw(house_m);

    display();
    }

return 0;
}
