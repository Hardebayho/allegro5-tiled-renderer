#pragma once
#include <Tmx.h>
#include <allegro5/allegro.h>
#include "RendererTileset.h"
#include "TileLayerRenderer.h"
#include "ObjectLayerRenderer.h"
#include "GroupLayerRenderer.h"
#include "ImageLayerRenderer.h"

class MapRenderer {
public:
    /// The map renderer constructor. Initializes the map and loads all required tilesets.
    /// Also takes a string parameter, that specifies the path to the tilesets folder
    MapRenderer(Tmx::Map* map, std::string tilesetFolder);
    ~MapRenderer();
    /// This changes the tiled map to be rendered. Note that you'll still have to initialize the map yourself, and delete the previous map. This renderer doesn't free any resources you pass to it (including the map), so you have to free those resources yourself. It frees all the loaded textures and images though
    void changeMap(Tmx::Map* newMap);
    
    /// Loads all the tilesets
    void loadTilesets();
    
    /// Draws the map to the screen.
    /// The sx and sy represents the position to start drawing from in the map, and sWidth and sHeight specifies 'how much' of the map to draw on the screen. The dx and dy specifies where to start drawing our map on our actual screen
    void draw(float sx, float sy, float sWidth, float sHeight, float dx, float dy);
    
    /// Deallocate all the loaded images.
    void dispose();
    
private:
    Tmx::Map* _map;
    
    std::string getResolvedPath(std::string pathToResolve);
    
    
    // --------------------------- //
    RendererTileset* _tileset;
    std::string _pathToTileset;
    int _numTilesets;
    TileLayerRenderer* _tileLayerRenderer;
    ObjectLayerRenderer* _objectLayerRenderer;
    GroupLayerRenderer* _groupLayerRenderer;
    ImageLayerRenderer* _imageLayerRenderer;
    
};
