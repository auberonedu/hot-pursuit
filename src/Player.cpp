#include <bn_keypad.h>
#include "Player.h"
#include "bn_sprite_items_robber.h"

bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size) {
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

void Player::update() {
    if(bn::keypad::right_held()) {
        sprite.set_x(sprite.x() + SPEED);
    }
    if(bn::keypad::left_held()) {
        sprite.set_x(sprite.x() - SPEED);
    }

    // TODO: Add logic for up and down
    if(bn::keypad::up_held()) {
        sprite.set_y(sprite.y() - SPEED);
    }
    if(bn::keypad::down_held()) {
        sprite.set_y(sprite.y() + SPEED);
    }

    //If player tries to go out of bounds, prevent player from going out of bounds
    //If player moves too far right
    if(sprite.x() > MAX_X) {
        sprite.set_x(MAX_X);
    }
    //If player moves too far left
    if(sprite.x() < MIN_X) {
        sprite.set_x(MIN_X);
    }
    //If player moves too far bottom
    if(sprite.y() > MAX_Y) {
        sprite.set_y(MAX_Y);
    }
    //If player moves too far top
    if(sprite.y() < MIN_Y) {
        sprite.set_y(MIN_Y);
    }



    bounding_box = create_bounding_box(sprite, size);
};

Player::Player() : 
        sprite(bn::sprite_items::robber.create_sprite(X_START, Y_START)), speed(SPEED), size(PLAYER_SIZE), 
        bounding_box(create_bounding_box(sprite, size)) {};

