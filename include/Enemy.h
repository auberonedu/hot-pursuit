#pragma once
#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_random.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_keypad.h>

#include "Player.h"


class Enemy{
    public:
     bn::sprite_ptr sprite;
     bn::fixed x_speed;
     bn::fixed y_speed;
     bn::size size;
     bn::random rng;
     bn::rect bounding_box;
  
         Enemy(bn::fixed x_start, bn::fixed y_start,bn::fixed speed);

         //ScoreDisplay score_display= ScoreDisplay();

         void update(Player& player);
};