#include "TileLayerRenderer.h"
#include <iostream>

TileLayerRenderer::TileLayerRenderer() {}

void TileLayerRenderer::drawOrthogonalTileLayer(Tmx::TileLayer *layer, RendererTileset* tilesets, float sx, float sy, float sWidth, float sHeight, float dx, float dy) {
    if (!layer->IsVisible()) return; // We don't want to draw an invisible layer
    
    int tileWidth = layer->mapGetMap()->GetTileWidth();
    int tileHeight = layer->mapGetMap()->GetTileHeight();

    float rowOffset = sy / tileHeight;
    float colOffset = sx / tileWidth;
    int numRowsToDraw = sHeight / tileHeight + 1;
    int numColsToDraw = sWidth / tileWidth + 1;
    
    float tileRowOffset = (rowOffset - (int)rowOffset) * tileHeight;
    float tileColOffset = (colOffset - (int)colOffset) * tileWidth;
    
    int diffX = layer->mapGetMap()->GetWidth();
    int diffY = layer->mapGetMap()->GetHeight();
    
    if (diffX < numColsToDraw) {
        numColsToDraw = diffX - 1;
        colOffset = 0;
    }

    if (diffY < numRowsToDraw) {
        numRowsToDraw = diffY - 1;
        rowOffset = 0;
    }
    
    // This speeds up rendering of the layer
    al_hold_bitmap_drawing(true);
    
    // Get all the tiles in the tile layer
    for (int row = 0; row <= numRowsToDraw; row++) {
        for (int col = 0; col <= numColsToDraw; col++) {
            // Get a tile
            const Tmx::MapTile tile = layer->GetTile(col + colOffset, row + rowOffset);
            
            if (row + rowOffset >= diffY) {
                continue;
            }

            if (tile.gid <= 0 || tile.tilesetId >= layer->mapGetMap()->GetTilesets().size()) {
                continue;
            }
            
            // Get associated tileset of the tile
            const Tmx::Tileset* tileset = layer->mapGetMap()->GetTileset(layer->mapGetMap()->FindTilesetIndex(tile.gid));
            
            if (!tileset) {
                continue;
            }
            
            int id = tile.gid - tileset->GetFirstGid();
            
            if (id < 0) continue;
            
            int flags = 0;
            
            if (tile.flippedHorizontally) {
                flags |= ALLEGRO_FLIP_HORIZONTAL;
            }
            
            if (tile.flippedVertically) {
                flags |= ALLEGRO_FLIP_VERTICAL;
            }
            
            // Get the number of rows and columns for our tileset
            int numCols = tileset->GetColumns();
            
            if (numCols <= 0) {
                std::cout << "This tileset has got no columns." << std::endl;
                continue;
            }
            
            // Retrieve the current tile row and column to access our tile image in the tile set
            int currTileRow = id / numCols;
            int currTileCol = id % numCols;
            
            float width = layer->mapGetMap()->GetTileWidth();
            float height = layer->mapGetMap()->GetTileHeight();
            
            // Get the tileset name, and get the associated loaded bitmap.
            ALLEGRO_BITMAP* ts = tilesets->getTileset(tileset->GetName());
            
            //ALLEGRO_BITMAP* subimage = al_create_sub_bitmap(ts, currTileCol * width, currTileRow * height, width, height);
            
           // al_draw_bitmap(subimage, dx + col * width - tileColOffset, dy + row * height - tileRowOffset, flags);
            al_draw_bitmap_region(ts, currTileCol * width, currTileRow * height, width, height, dx + col * width - tileColOffset, dy + row * height - tileRowOffset, flags);
        }
    }
    
    al_hold_bitmap_drawing(false);
    
}
