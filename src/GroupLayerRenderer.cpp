#include "GroupLayerRenderer.h"

GroupLayerRenderer::GroupLayerRenderer(std::string tilesetFolder) : _tilesetFolder(tilesetFolder) {
  _tileLayerRenderer = new TileLayerRenderer();
  _objectLayerRenderer = new ObjectLayerRenderer();
  _imageLayerRenderer = new ImageLayerRenderer(tilesetFolder);
}

void GroupLayerRenderer::drawGroupLayer(Tmx::GroupLayer *layer, RendererTileset *tilesets, float sx, float sy, float sWidth, float sHeight, float dx, float dy) {
  
  if (!layer->IsVisible()) return;
  
  // Loop through all the layers
  for (auto& data : layer->GetChildren()) {
    if (data->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_TILE) {
      _tileLayerRenderer->drawOrthogonalTileLayer((Tmx::TileLayer*)data, tilesets, sx, sy, sWidth, sHeight, dx, dy);
    } else if (data->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_OBJECTGROUP) {
      _objectLayerRenderer->drawOrthogonalObjectLayer((Tmx::ObjectGroup*)data, tilesets, sx, sy, sWidth, sHeight, dx, dy);
    } else if (data->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_GROUP_LAYER) {
      drawGroupLayer((Tmx::GroupLayer*)data, tilesets, sx, sy, sWidth, sHeight, dx, dy);
    } else if (data->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_IMAGE_LAYER) {
        _imageLayerRenderer->drawImageLayer((Tmx::ImageLayer*)data, tilesets, dx, dy);
    }
  }
  
}

GroupLayerRenderer::~GroupLayerRenderer() {
  delete _tileLayerRenderer;
  delete _objectLayerRenderer;
    delete _imageLayerRenderer;
}
