#pragma once

#include <bn_fixed.h>
#include <bn_random.h>
#include <bn_rect.h>
#include <bn_size.h>

#include "player.h"

class Enemy {
    public:
        bn::sprite_ptr mob;
        bn::fixed speed; // The speed of the mob
        bn::size size; // The width and height of the mob
        bn::rect bounding_box; // The rectangle around the mob for checking collision

        Enemy(bn::fixed x, bn::fixed y, bn::fixed mob_speed, bn::size mob_size);

        void update(Player& player);
};

void enemy_position(Enemy& enemy, bn::random& rand);