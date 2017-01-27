#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;


class TileMap : public sf::Drawable, public sf::Transformable
{       private:
                VertexArray m_vertices;
                Texture m_tileset;
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

        public:
                TileMap();
                bool load(const std::string& tileset, Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
                bool loadt(const std::string& tileset, Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height,int i,int j);
                int* insertArray(const int[],const int[],int,int,Vector2u,Vector2u);

};
#endif
