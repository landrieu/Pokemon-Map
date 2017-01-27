#include "TileMap.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>


using namespace std;

TileMap::TileMap()
{

}

 bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
        // on charge la texture du tileset
        if (!m_tileset.loadFromFile(tileset))
          return false;

int r;
        // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
        m_vertices.setPrimitiveType(Quads);
        m_vertices.resize(width * height * 4);

          // on remplit le tableau de vertex, avec un quad par tuile
       for (unsigned int i = 0; i < width; ++i)
       {
            for (unsigned int j = 0; j < height; ++j)
            {
                // on récupère le numéro de tuile courant
                int tileNumber = tiles[i + j * width];

                // on en déduit sa position dans la texture du tileset
                int tu = (tileNumber % (m_tileset.getSize().x / tileSize.x));
                int tv = (tileNumber / (m_tileset.getSize().x / tileSize.x));

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // on définit ses quatre coins
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // on définit ses quatre coordonnées de texture
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                r=r+1;

            }}

 return true;
}
bool TileMap::loadt(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height,int a,int b)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        int r=0;

        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize((width+a) * (height+b) * 4);
        int e=m_tileset.getSize().x / tileSize.x;
        //cout<<"E "<<e;

                  for (unsigned int i = a; i < width+a; ++i)
		{
            		for (unsigned int j = b; j < height+b; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[(i-a) + ((j-b) * width)];

                // find its position in the tileset texture
                //int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                //int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                 sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                quad[0].position = sf::Vector2f(i*tileSize.x,j*tileSize.y);
                quad[1].position = sf::Vector2f((i*tileSize.x)+tileSize.x,j*tileSize.y);
                quad[2].position = sf::Vector2f((i*tileSize.x)+tileSize.x,(j*tileSize.y)+tileSize.y);
                quad[3].position = sf::Vector2f((i*tileSize.x),(j*tileSize.y)+tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f((tileNumber%e)*tileSize.x,((tileNumber/e)*tileSize.y));
                quad[1].texCoords = sf::Vector2f(((tileNumber%e)*tileSize.x)+tileSize.x, ((tileNumber/e)*tileSize.y));
                quad[2].texCoords = sf::Vector2f(((tileNumber%e)*tileSize.x)+tileSize.x, (((tileNumber/e)*tileSize.y))+tileSize.y);
                quad[3].texCoords = sf::Vector2f((tileNumber%e)*tileSize.x, ((tileNumber/e)*tileSize.y)+tileSize.y);

r=r+1;
		}}

        return true;
    }




void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &m_tileset;

        // et on dessine enfin le tableau de vertex
        target.draw(m_vertices, states);
}
