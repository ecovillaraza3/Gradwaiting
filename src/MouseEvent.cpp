#include "MouseEvent.h"

bool MouseEvent::isMouseClicked(int x, int y, int w, int h, SDL_Event event){
    bool stat = false;

    if(
       x+w > event.motion.x &&
       y+h > event.motion.y &&
       event.motion.x > x &&
       event.motion.y > y
       ){
        stat = true;
    }

    return stat;
}
