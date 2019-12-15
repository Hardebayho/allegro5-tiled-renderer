#include "RendererTileset.h"

RendererTileset::RendererTileset() {}

ALLEGRO_BITMAP* RendererTileset::getTileset(std::string name) {
    if (_tilesets.count(name) > 0) {
        ALLEGRO_BITMAP* image = _tilesets.at(name);
        return image;
    }
    return nullptr;
}

void RendererTileset::addTileset(std::string name, ALLEGRO_BITMAP *tileset) {
    _tilesets.emplace(name, tileset);
}

void RendererTileset::dispose() {
    
    for (auto& data : _tilesets) {
        al_destroy_bitmap(data.second);
    }
    
    _tilesets.clear();
    
}