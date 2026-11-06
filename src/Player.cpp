#include "Player.h"
#include "ScoreDisplay.h"
#include "bn_sprite_items_cat.h"
#include "bn_sprite_items_mouse.h"
#include "boundingBox.h"
//#include <bn_keypad.h>

static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::fixed PLAYER_SPEED = 2;
static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;


Player:: Player(bn::fixed x_start, bn::fixed y_start) : 
            sprite(bn::sprite_items::mouse.create_sprite(x_start, y_start)),
            x_speed(PLAYER_SPEED),
             y_speed(PLAYER_SPEED),
            size(PLAYER_SIZE){
                bounding_box = create_bounding_box(sprite, size);
        }

void Player:: returnToScreen(){
    // .x returns the horizontal position of the sprite
        // If the sprite moves to the left, it will come back to the right.
        if (sprite.x() < MIN_X)
        {
        // .set_x sets the horizontal position of the sprite
        // just using the max/min/ already available
        sprite.set_x(MAX_X);
        }

        // if sprite moves to the right, it will come back on the left
        if (sprite.x() > MAX_X)
        {
        sprite.set_x(MIN_X);
        }
        // if sprite goes up,will show up again at the bottom
        // .y returns the vertical position of the sprite
        if (sprite.y() < MIN_Y)
        {
        // .set_y will set the vertical position of the sprite
        sprite.set_y(MAX_Y);
        }
        // if sprite goes down it will come back from top of screen
        if (sprite.y() > MAX_Y)
        {
        sprite.set_y(MIN_Y);
        }
}

    void Player:: speed(){
                

        if (bn::keypad::right_held() )
        {

            sprite.set_x(sprite.x() + x_speed);
        }
        if (bn::keypad::left_held())
        {
            sprite.set_x(sprite.x() - x_speed);
        }
        // TODO: Add logic for up and down
        if (bn::keypad::up_held())
        {
            sprite.set_y(sprite.y() - y_speed);
        }
        if (bn::keypad::down_held())
        {
            sprite.set_y(sprite.y() + y_speed);
        }

         bounding_box = create_bounding_box(sprite, size);
    }

       

