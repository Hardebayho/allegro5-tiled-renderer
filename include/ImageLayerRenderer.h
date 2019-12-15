#ifndef IMAGELAYERRENDERER_H
#define IMAGELAYERRENDERER_H
#include <Tmx.h>
#include "RendererTileset.h"

class ImageLayerRenderer
{
public:
    ImageLayerRenderer(std::string tilesetFolder);
    void drawImageLayer(Tmx::ImageLayer* imageLayer, RendererTileset* tileset, float dx, float dy);
private:
    std::string _pathToTileset;
};

#endif // IMAGELAYERRENDERER_H
