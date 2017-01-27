#include <iostream>
#include "Jeu.hpp"
#include "TileMap.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Jeu jeu;
    jeu.jouer();
    return 0;
}
