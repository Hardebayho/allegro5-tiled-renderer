#pragma once
#include <Tmx.h>
#include <allegro5/allegro.h>
#include "RendererTileset.h"

class TileLayerRenderer {
    
public:
    /// Instantiate this tile layer renderer
    TileLayerRenderer();
    /// Draws an orthogonal tile layer as specified by the caller
    void drawOrthogonalTileLayer(Tmx::TileLayer* layer, RendererTileset* tilesets, float sx, float sy, float sWidth, float sHeight, float dx, float dy);
    
private:
};

