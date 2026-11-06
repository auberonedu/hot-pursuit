#pragma once
#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_rect.h>


class Player{
    public:
     bn::sprite_ptr sprite;
     bn::fixed x_speed;
     bn::fixed y_speed;
     bn::size size;
    bn::rect bounding_box;
    
    Player(bn::fixed x_start, bn::fixed y_start);


    void returnToScreen();

    void speed();
};