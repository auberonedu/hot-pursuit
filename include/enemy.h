#pragma once

#include <bn_sprite_ptr.h>
#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_random.h>
#include <bn_rect.h>

#include "Player.h"


bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size);

static constexpr int ENEMY_X_START = 67;
static constexpr int ENEMY_Y_START = 10;



static constexpr int MAX_ENEMIES = 10;



class Enemy {

/*a sprite_ptr for its sprite
a size for the size
a rect for a bounding box
a constructor that takes a starting_x, starting_y, and size and initializes ALL values
*/  
    public:

    void update(Player& player);
    
    bn::sprite_ptr sprite; // bn::sprite_items::dot.create_sprite();
    bn::fixed speed; // The speed of the player
    bn::size size; // The width and height of the sprite
    bn::rect enemy_bounding_box; // The rectangle around the sprite for checking collision
    bn::random random;
    bool player_caught = false;



    //constructor
    Enemy(bn::fixed x_start, bn::fixed y_start, bn::fixed enemySpeed);
};
