#pragma once

#include <bn_sprite_ptr.h>
#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_display.h>

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};

//Starting position of the player
static constexpr int X_START = 44;
static constexpr int Y_START = 22;

//Speed of the player
static constexpr bn::fixed SPEED = 2.5;

bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size);


class Player {
    public:
        /**
         * Update the position and bounding box of the player based on d-pad movement.
         */
        void update();

         // Create the sprite. This will be moved to a constructor
        bn::sprite_ptr sprite; // bn::sprite_items::dot.create_sprite();
        bn::fixed speed; // The speed of the player
        bn::size size; // The width and height of the sprite
        bn::rect bounding_box; // The rectangle around the sprite for checking collision

        Player();
};