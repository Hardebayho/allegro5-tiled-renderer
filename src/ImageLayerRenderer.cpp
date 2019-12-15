#include "ImageLayerRenderer.h"
#include <iostream>

ImageLayerRenderer::ImageLayerRenderer(std::string tilesetFolder) : _pathToTileset(tilesetFolder) {}

void ImageLayerRenderer::drawImageLayer(Tmx::ImageLayer* imageLayer, RendererTileset* tileset, float dx, float dy) {
    // Get a bitmap of our image. If it doesn't exist, load one and add it to the RendererTileset
    ALLEGRO_BITMAP* image = tileset->getTileset(imageLayer->GetName());
    if (!image) {
        std::cout << "Image not loaded! Loading and caching the image..." << std::endl;
        // Load the bitmap and put it inside the RendererTileset for reuse
        image = al_load_bitmap((_pathToTileset + "/" + imageLayer->GetImage()->GetSource()).c_str());
        if (!image) {
            std::cout << "Could not load image from the image layer!" << std::endl;
            std::cout << "Path: " << _pathToTileset + "/" + imageLayer->GetImage()->GetSource().c_str() << std::endl;
        } else {
            std::cout << "Loaded image successfully!" << std::endl;
        }
        tileset->addTileset(imageLayer->GetName(), image);
    }

    al_draw_bitmap(image, dx + imageLayer->GetX(), dy + imageLayer->GetY(), 0);
}
