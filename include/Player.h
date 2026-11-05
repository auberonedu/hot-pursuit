#pragma once

#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_rect.h>
#include "PowerUp.h"

class Player
{
public:
    bn::sprite_ptr sprite;
    bn::fixed speed;
    bn::size size;
    bn::rect bounding_box;
    int speed_timer;
    int invincible_timer;

    void update();
    void apply_power_up(PowerUpType type);
    bool is_invincible() const;

    Player(bn::fixed x_start, bn::fixed y_start);
};