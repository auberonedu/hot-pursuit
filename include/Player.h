#pragma once

#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_keypad.h>

class Player
{
public:
    bn::sprite_ptr sprite; // Sprite Initializer
    bn::fixed speed;       // The speed of the player
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision
    /**
     * Update the position and bounding box of the player based on d-pad movement.
     */
    void update();

    Player(bn::fixed x_start, bn::fixed y_start);
};