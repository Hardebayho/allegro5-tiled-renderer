#pragma once
#include <Tmx.h>
#include <allegro5/allegro.h>
#include "RendererTileset.h"

class ObjectLayerRenderer {
  public:
      /// Instantiates the ObjectLayerRenderer
      ObjectLayerRenderer();
      
      /// Draws the drawable contents of the object layer
      void drawOrthogonalObjectLayer(Tmx::ObjectGroup* group, RendererTileset* tilesets, float sx, float sy, float sWidth, float sHeight, float dx, float dy);
};
