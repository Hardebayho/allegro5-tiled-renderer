#pragma once
#include <string>
#include <allegro5/allegro.h>
#include <map>

class RendererTileset {
public:
    RendererTileset();
    /// Gets the tileset based on the names
    ALLEGRO_BITMAP* getTileset(std::string name);
    /// Adds a tileset to this rendertileset.
    void addTileset(std::string name, ALLEGRO_BITMAP* tileset);
    /// Returns all the tilesets as an array
    std::map<std::string, ALLEGRO_BITMAP*> &getTilesets() { return _tilesets; }
    
    void dispose();
    
private:
    std::map<std::string, ALLEGRO_BITMAP*> _tilesets;
};