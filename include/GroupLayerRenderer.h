#pragma once
#include <Tmx.h>
#include "ObjectLayerRenderer.h"
#include "TileLayerRenderer.h"
#include "ImageLayerRenderer.h"
#include "RendererTileset.h"

class GroupLayerRenderer {
public:
  GroupLayerRenderer(std::string tilesetFolder);
  void drawGroupLayer(Tmx::GroupLayer *layer, RendererTileset* tilesets, float sx, float sy, float sWidth, float sHeight, float dx, float dy);
  
  ~GroupLayerRenderer();
  
private:
  std::string _tilesetFolder;
  TileLayerRenderer* _tileLayerRenderer;
  ObjectLayerRenderer* _objectLayerRenderer;
  ImageLayerRenderer* _imageLayerRenderer;
  
};
