#pragma once

#include <GameObject.h>
#include <Logger.h>
#include <Sprite.h>
#include <Util.h>

#include <string>

class TileSet {
    public:
    
        TileSet(GameObject&, int, int, std::string);
        
        void RenderTile(unsigned int, float, float);

        unsigned int GetQuantityTiles() const;

        int GetTileWidth() const;

        int GetTileHeight() const;

    private:

        Sprite tileSet;

        int rows;

        int columns;

        int tileWidth;

        int tileHeight;

};