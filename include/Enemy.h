#pragma once

#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_keypad.h>

#include "Player.h"

class Enemy
{
public:
    bn::sprite_ptr sprite; // Sprite Initializer
    bn::fixed speed;       // The speed of the enemy
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision
    Player &player;

    void update();

    Enemy(bn::fixed x_start, bn::fixed y_start, Player &player_ref, double player_speed);
};