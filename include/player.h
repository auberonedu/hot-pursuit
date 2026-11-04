#pragma once

#include <bn_fixed.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>
#include "bn_sprite_items_dot.h"

// Helper function declaration (assuming this is defined somewhere or in a utility header)
bn::rect create_bounding_box(const bn::sprite_ptr& sprite, bn::size size);

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