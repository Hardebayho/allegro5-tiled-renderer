#include "MapRenderer.h"
#include <iostream>
#include <bits/stdc++.h>

MapRenderer::MapRenderer(Tmx::Map* map, std::string tilesetFolder) : _map(map), _pathToTileset(tilesetFolder) {
    _tileset = new RendererTileset();
    loadTilesets();
    _tileLayerRenderer = new TileLayerRenderer();
    _objectLayerRenderer = new ObjectLayerRenderer();
    _groupLayerRenderer = new GroupLayerRenderer(tilesetFolder);
    _imageLayerRenderer = new ImageLayerRenderer(tilesetFolder);
}

std::string MapRenderer::getResolvedPath(std::string pathToResolve) {
    
    // We're going to use string tokenizer to get the last path of the file here.
    std::vector<std::string> tokens;
    std::stringstream stream(pathToResolve);
    
    std::string intermediate;
    
    // Put each token into the tokens vector
    while (getline(stream, intermediate, '/')) {
        tokens.push_back(intermediate);
    }
    
    if (_pathToTileset.empty())
        return tokens.back();
    
    // Concatenate this thing and return it
    return _pathToTileset + "/" + tokens.back();
}


void MapRenderer::loadTilesets() {
    std::cout << "Loading tilesheets..." << std::endl;
    // Load required tilesets
    _numTilesets = _map->GetNumTilesets();
    for (int i = 0; i < _numTilesets; i++) {
        const Tmx::Tileset* ts = _map->GetTileset(i);
        std::string name = ts->GetName();
        std::string image_path = getResolvedPath(ts->GetImage()->GetSource());
        
        ALLEGRO_BITMAP* image = al_load_bitmap(image_path.c_str());
        if (!image) {
            std::cout << "Could not load tileset bitmap: " << image_path << std::endl;
        }
        _tileset->addTileset(name, image);
    }
    
    std::cout << "Tilesheets loaded" << std::endl;
}

void MapRenderer::changeMap(Tmx::Map *newMap) {
    _map = newMap;
    
    // Delete and deallocate old map bitmaps
    _tileset->dispose();
    
    // Load required tilesets
    loadTilesets();
}

void MapRenderer::draw(float sx, float sy, float sWidth, float sHeight, float dx, float dy) {
    
    // Draw on the screen only if the map is an orthogonal map. We don't support other map types (yet), so we don't draw them
    if (_map->GetOrientation() == Tmx::MapOrientation::TMX_MO_ORTHOGONAL) {
        for (const Tmx::Layer* layer : _map->GetLayers()) {
            if (layer->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_TILE) {
                _tileLayerRenderer->drawOrthogonalTileLayer((Tmx::TileLayer*)layer, _tileset, sx, sy, sWidth, sHeight, dx, dy);
            } else if (layer->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_OBJECTGROUP) {
                _objectLayerRenderer->drawOrthogonalObjectLayer((Tmx::ObjectGroup*)layer, _tileset, sx, sy, sWidth, sHeight, dx, dy);
            } else if (layer->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_GROUP_LAYER) {
                Tmx::GroupLayer* groupLayer = (Tmx::GroupLayer*)layer;
                _groupLayerRenderer->drawGroupLayer(groupLayer, _tileset, sx, sy, sWidth, sHeight, dx, dy);
            } else if (layer->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_IMAGE_LAYER) {
                Tmx::ImageLayer* imageLayer = (Tmx::ImageLayer*)layer;
                _imageLayerRenderer->drawImageLayer(imageLayer, _tileset, dx, dy);
            }
        }
    }
}

MapRenderer::~MapRenderer() {
}

void MapRenderer::dispose() {
    // Dispose of the entire tilesets
    _tileset->dispose();
    delete _tileset;
    
    delete _tileLayerRenderer;
    delete _objectLayerRenderer;
    delete _groupLayerRenderer;
    delete _imageLayerRenderer;
}
