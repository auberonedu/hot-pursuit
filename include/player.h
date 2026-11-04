#pragma once

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_dot.h"
#include "bn_fixed.h"
#include "bn_size.h"
#include "bn_rect.h"
#include "bn_keypad.h"

class Player {
public:
    bn::sprite_ptr sprite;
    bn::fixed speed;
    bn::size size;
    bn::rect bounding_box;

    //constructor
    Player(bn::fixed x, bn::fixed y, bn::fixed player_speed, bn::size player_size);

    void update();
};

#endif