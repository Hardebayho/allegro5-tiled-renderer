#include "ObjectLayerRenderer.h"

ObjectLayerRenderer::ObjectLayerRenderer() {}

void ObjectLayerRenderer::drawOrthogonalObjectLayer(Tmx::ObjectGroup *group, RendererTileset *tilesets, float sx, float sy, float sWidth, float sHeight, float dx, float dy) {
    // Draw only if visible
    if (!group->IsVisible()) return;
    
    al_hold_bitmap_drawing(true);
    // Get all the objects of the object group
    for (Tmx::Object* object : group->GetObjects()) {
        
        float objectX = object->GetX();
        float objectY = object->GetY();
        float objectWidth = object->GetWidth();
        float objectHeight = object->GetHeight();
        
        // Let's see if this object has got a tileset
        int gid = object->GetGid();
        if (gid < 1) continue; // We're not drawing objects without a tileset
        
        const Tmx::Tileset* tileset = group->mapGetMap()->FindTileset(gid);
        if (!tileset) continue;
        
        int tileID = gid - tileset->GetFirstGid();
        if (tileID < 0) continue;
        
        int numCols = tileset->GetColumns();
        
        int currTileRow = tileID / numCols;
        int currTileCol = tileID % numCols;
        
        int x = objectX - sx;
        int y = objectY - sy;
        
        // Check here to make sure that we're drawing an object on the screen
        if ((x + objectWidth) < 0 || x > sWidth || y < 0 || (y - objectHeight) > sHeight) continue;
        
        ALLEGRO_BITMAP* ts = tilesets->getTileset(tileset->GetName());
        //ALLEGRO_BITMAP* subimage = al_create_sub_bitmap(ts, currTileCol * objectWidth, currTileRow * objectHeight, objectWidth, objectHeight);
        
        //al_draw_bitmap(subimage, dx + x, dy + y - objectHeight, 0);
        al_draw_bitmap_region(ts, currTileCol * objectWidth, currTileRow * objectHeight, objectWidth, objectHeight, dx + x, dy + y - objectHeight, 0);
    }
    al_hold_bitmap_drawing(false);
    
}
