#include <MapRenderer.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>

#include <Tmx.h>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main() {
    
    Tmx::Map* map = new Tmx::Map();
    
    map->ParseFile("test_data/csv.tmx");
    
    float mapx = 0;
    float mapy = 0;
    
    if (map->HasError()) {
        std::cout << "An error occured when parsing the map. Error: " << map->GetErrorText() << std::endl;
    }
    
    if (!al_init()) std::cout << "Could not initialize Allegro 5 library." << std::endl;
    al_init_image_addon();
    al_install_keyboard();
    ALLEGRO_DISPLAY* display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0/60);
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    MapRenderer* renderer = new MapRenderer(map, "test_data");
    
    ALLEGRO_KEYBOARD_STATE key_state;
    
    ALLEGRO_EVENT event;
    
    bool running = true;
    
    al_start_timer(timer);
    while (running) {
        
        al_wait_for_event(event_queue, &event);
        
        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            running = false;
            break;
        case ALLEGRO_EVENT_TIMER:
            
            al_get_keyboard_state(&key_state);
            
            // Handle input before rendering
            if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT)) {
                mapx += 6;
                
                if (mapx > map->GetWidth() * map->GetTileWidth() - WINDOW_WIDTH) {
                    mapx = map->GetWidth() * map->GetTileWidth() - WINDOW_WIDTH;
                }
                
            } else if (al_key_down(&key_state, ALLEGRO_KEY_LEFT)) {
                mapx -= 6;
                if (mapx < 0) {
                    mapx = 0;
                }
            }
            
            if (al_key_down(&key_state, ALLEGRO_KEY_DOWN)) {
                mapy += 6;
                if (mapy >= map->GetHeight() * map->GetTileHeight() - WINDOW_HEIGHT) {
                    mapy = map->GetHeight() * map->GetTileHeight() - WINDOW_HEIGHT;
                }
            } else if (al_key_down(&key_state, ALLEGRO_KEY_UP)) {
                mapy -= 6;
                if (mapy < 0) mapy = 0;
            }
            
            al_clear_to_color(al_map_rgb(100, 10, 10));
            // Update and render stuff here
            renderer->draw(mapx, mapy, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
            
            al_flip_display();
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            // Key down event
            break;
        case ALLEGRO_EVENT_KEY_UP:
            // Key up event
            break;
        }
        
    }
    
    delete map;
    
    renderer->dispose();
    delete renderer;
    
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    
    return 0;
}
